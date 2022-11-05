#include "pch.h"
#include "Room.h"

#include <random>

#include "ServerPacketHandler.h"

int Room::AddSession(GameSessionRef session)
{
	WRITE_LOCK_IDX(0);
	if (playerCount == MAXPLAYER)
		return false;
	ASSERT_CRASH(playerCount <= MAXPLAYER);
	_sessions.insert({ session->_key,session });
	playerCount++;
	return true;
}

bool Room::RemoveSession(GameSessionRef session)
{
	WRITE_LOCK_IDX(0);
	ASSERT_CRASH(playerCount >0);
	_sessions.erase(session->_key);
	playerCount--;
	return true;
}

void Room::Clear()
{
	for (auto session : _sessions)
	{
		session.second->_ready = false;
	}
	_sessions.clear();
	roomState = state::MATCHING;
}

bool Room::isFull()
{
	READ_LOCK_IDX(0);
	return playerCount == MAXPLAYER;
}

bool Room::isReady()
{
	if (playerCount == 0)
		return false;

	if (roomState == state::START)
		return false;

	for (auto& session : _sessions)
	{
		if (session.second->_ready == false)
			return false;
	}
	return true;
}


void Room::AddData(string key, bool dir, bool onOff)
{
	P_Event();
	WRITE_LOCK_IDX(1);
	auto input = movePkt[pktIdx].add_inputs();

	input->set_code(key);
	input->set_direction(dir);
	input->set_onoff(onOff);
}

//void Room::BroadcastData(Protocol::S_MOVE data)
//{
//	const uint16 dataSize = static_cast<uint16> (data.ByteSizeLong());
//	const uint16 PacketSize = dataSize + sizeof(PacketHeader);
//
//	auto sendBuffer = new char[PacketSize];
//
//
//
//	DWORD sendLen = 0;
//	DWORD flags = 0;
//	PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer);
//	header->size = PacketSize;
//	header->id = PACKET_TYPE::S_MOVE;
//
//	data.SerializeToArray(&header[1], dataSize);
//	WSABUF wsaBuf;
//	wsaBuf.buf = sendBuffer;
//	wsaBuf.len = PacketSize;
//
//
//	for (auto& session : _sessions)
//	{
//		SessionRef _session = session.second;
//		if(WSASend(_session->GetSocket(), &wsaBuf, 1, &sendLen, flags, nullptr, nullptr) == SOCKET_ERROR)
//		{
//			int32 error = WSAGetLastError();
//			if (error != WSA_IO_PENDING)
//				ASSERT_CRASH("boo");
//		}
//	}
//}

void Room::Broadcast(SendBufferRef buffer)
{
	P_Event();
	for(auto& session : _sessions)
	{
		session.second->Send(buffer);
	}
}
/*HACK: Broadcast는 중첩 실행되지 않는다고 가정함(한 방의 Broadcast는 충분한 간격을 두고 실행)
 * 잡 방식 변경시 생각해봐야 함
 *
 */
void Room::BroadcastData()
{

	int32 oldIndex = -1;
	{
		P_Event("SWAP Data");
		WRITE_LOCK_IDX(1);
		oldIndex = pktIdx;
		pktIdx = pktIdx == 0 ? 1 : 0;
	}
	{
		WRITE_LOCK_IDX(0);
		auto buffer = ServerPacketHandler::MakeSendBuffer(movePkt[oldIndex]);
		for (auto& session : _sessions)
		{
			session.second->Send(buffer);
		}
		movePkt[oldIndex].Clear();
	}
	if(GetState() == START)
		DoTimer(50, &Room::BroadcastData);
}


void Room::Send(SendBufferRef buffer, GameSessionRef session)
{
	session->Send(buffer);
}

void Room::WaitPlayer()
{

	{ WRITE_LOCK_IDX(0); roomState = READY; }

	Protocol::S_ENTER_GAME pkt;

	std::mt19937 gen(GRoomManager.rd());
	std::uniform_real_distribution<float> dis(-1, 1);
	for (auto& session : _sessions)
	{
		auto a = pkt.add_players();
		a->set_code(session.second->_key);
		a->set_name("Test");
		float data = dis(gen);
		a->set_startvector(data);
	}

	pkt.set_roomnumber(roomNumber);
	pkt.set_success(true);

	Broadcast(ServerPacketHandler::MakeSendBuffer(pkt));
}

void Room::PlayStart()
{
	{ WRITE_LOCK_IDX(0); roomState = state::START; }

	cout << "Room " + std::to_string(roomNumber) + " start" << endl;

	Protocol::S_START pkt;
	Broadcast(ServerPacketHandler::MakeSendBuffer(pkt));

	DoTimer(50, &Room::BroadcastData);
}

void Room::RoomCheck()
{
	P_Event();
	int32 tick = GetTickCount();
	if (isFull() == false) {
		DoTimer(200, &Room::RoomCheck);
		return;
	}

	switch (GetState())
	{
	case Room::MATCHING:
		cout << "room Ready" << endl;
		WaitPlayer();
		break;
	case Room::READY:
		if (isReady())
		{
			PlayStart();
		}
		break;
	case Room::START:  // NOLINT(bugprone-branch-clone)
		break;
	default:
		break;
	}

	DoTimer(200, &Room::RoomCheck);
	
}
