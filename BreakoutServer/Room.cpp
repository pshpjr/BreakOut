#include "pch.h"
#include "Room.h"

#include <random>

#include "ServerPacketHandler.h"

int Room::AddSession(GameSessionRef session)
{
	WRITE_LOCK;
	if (playerCount == MAXPLAYER)
		return false;
	ASSERT_CRASH(playerCount <= MAXPLAYER);
	_sessions.insert(session);
	playerCount++;
	return true;
}

//bool Room::RemoveSession(GameSessionRef session)
//{
//	WRITE_LOCK;
//	ASSERT_CRASH(playerCount >0);
//	_sessions.erase(session->_key);
//	playerCount--;
//	return true;
//}

void Room::Clear()
{
	for (auto session : _sessions)
	{
		session->_ready = false;
	}
	_sessions.clear();
	roomState = state::MATCHING;
}

bool Room::isFull()
{
	READ_LOCK;
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
		if (session->_ready == false)
			return false;
	}
	return true;
}


void Room::Broadcast(Protocol::S_MOVE data)
{
	const uint16 dataSize = static_cast<uint16> (data.ByteSizeLong());
	const uint16 PacketSize = dataSize + sizeof(PacketHeader);

	auto sendBuffer = new char[PacketSize];



	DWORD sendLen = 0;
	DWORD flags = 0;
	PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer);
	header->size = PacketSize;
	header->id = PACKET_TYPE::S_MOVE;

	data.SerializeToArray(&header[1], dataSize);
	WSABUF wsaBuf;
	wsaBuf.buf = sendBuffer;
	wsaBuf.len = PacketSize;


	for (auto& session : _sessions)
	{
		SessionRef _session = session;
		if(WSASend(_session->GetSocket(), &wsaBuf, 1, &sendLen, flags, nullptr, nullptr) == SOCKET_ERROR)
		{
			int32 error = WSAGetLastError();
			if (error != WSA_IO_PENDING)
				ASSERT_CRASH("boo");
		}
	}
}

void Room::Broadcast(SendBufferRef buffer)
{
	P_Event();
	for(auto& session : _sessions)
	{
		session->Send(buffer);
	}
}



void Room::Send(SendBufferRef buffer, GameSessionRef session)
{
	session->Send(buffer);
}

void Room::WaitPlayer()
{

	{ WRITE_LOCK; roomState = READY; }

	Protocol::S_ENTER_GAME pkt;

	std::mt19937 gen(GRoomManager.rd());
	std::uniform_real_distribution<float> dis(-1, 1);
	for (auto& session : _sessions)
	{
		auto a = pkt.add_players();
		a->set_code(session->_key);
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
	{ WRITE_LOCK; roomState = state::START; }

	cout << "Room " + std::to_string(roomNumber) + " start" << endl;

	Protocol::S_START pkt;
	Broadcast(ServerPacketHandler::MakeSendBuffer(pkt));
}
