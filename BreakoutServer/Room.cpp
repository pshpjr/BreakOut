#include "pch.h"
#include "Room.h"

#include <random>

#include "GlobalQueue.h"
#include "Player.h"
#include "ServerPacketHandler.h"

void Room::AddSession(GameSessionRef session)
{
	if (playerCount == MAXPLAYER)
	{
		if (roomNumber == 99)
		{
			cout << "server Is Full" << endl;
			return;
		}
		GRoomManager->DoAsync(&RoomManager::AddPlayer, session, roomNumber+1);
		return;
	}

	ASSERT_CRASH(playerCount <= MAXPLAYER);
	_players[playerCount].SetSession(session);
	session->_roomNumber = roomNumber;
	++playerCount;

	Protocol::S_MACHING_GAME pkt;
	pkt.set_roomnumber(roomNumber);
	session->Send(ServerPacketHandler::MakeSendBuffer(pkt));
}

bool Room::RemoveSession(GameSessionRef session)
{

	auto player = FindPlayer(session);
	if (player == nullptr)
		return false;

	player->ClearSession();

	if (isPlay() == true)
	{
		player->setDead();
	}
	else
	{
		playerCount--;
	}

	return true;
}

Player* Room::FindPlayer(GameSessionRef session)
{
	Player* p = nullptr;
	for (auto& player : _players)
	{
		if (player.isEqualSession(session)) {
			p = &player;
		}
	}
	return p;
}

void Room::Clear()
{
	for (auto& p : _players)
	{
		p.ResetBreakout();
		p.ClearSession();
		p.ClearReady();
	}

	playerCount = 0;
	roomState = state::MATCHING;

	DoTimer(200, &Room::RoomCheck);
}

bool Room::isFull()
{
	return playerCount == MAXPLAYER;
}

bool Room::isReady()
{
	if (isFull() == false)
		return false;

	if (roomState == state::START)
		return false;

	for (auto& p : _players)
	{
		if (p.isReady() == false)
			return false;
	}
	return true;
}

void Room::Send(SendBufferRef buffer, GameSessionRef session)
{
	session->Send(buffer);
}

void Room::HandleReady(GameSessionRef session)
{
	if (isPlay() == false)
		session->Disconnect(L"Wrong Room");

	auto player = FindPlayer(session);
	if (player == nullptr)
		return;

	player->SetReadyTrue();
}

void Room::HandleInput(GameSessionRef session, Protocol::KeyInput input)
{
	if (isPlay() == false)
		session->Disconnect(L"Wrong Room");
	auto player = FindPlayer(session);
	if (player == nullptr)
		return;

	player->HandleInput(input);
}

void Room::Broadcast(SendBufferRef buffer)
{
	P_Event();
	for(auto& p : _players)
	{

		p.Send(buffer);
	}
}

void Room::BroadcastState()
{
	for (auto& p : _players)
	{
		auto input = movePkt.add_inputs();
	}
	DoTimer(200, &Room::BroadcastState);
}

void Room::RoomCheck()
{
	P_Event();

	if (isFull() == false) {
		DoTimer(200, &Room::RoomCheck);
		return;
	}

	switch (GetState())
	{
	case Room::MATCHING:

		WaitPlayer();
		break;
	case Room::READY:
		if (isReady())
		{
			PlayStart();
			return;
		}
		break;
	case Room::START:  // NOLINT(bugprone-branch-clone)
		break;
	case Room::ENDs:
		CRASH("가능함?")
		break;
	default:
		break;
	}

	DoTimer(200, &Room::RoomCheck);

}
void Room::WaitPlayer()
{
	cout << "room Ready : "<<roomNumber  << endl;
	roomState = READY;

	Protocol::S_ENTER_GAME pkt;

	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-1, 1);

	for (auto& session : _players)
	{
		auto a = pkt.add_players();
		a->set_code(session.GetKey());
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
	roomState = state::START;
	std::cout << "Room " + std::to_string(roomNumber) + " start" << endl;

	Protocol::S_START pkt;
	Broadcast(ServerPacketHandler::MakeSendBuffer(pkt));

	DoTimer(50, &Room::Update);
	DoTimer(200, &Room::BroadcastState);
}
void Room::PlayEnd()
{
	cout << "PlayEnd : "<<roomNumber << endl;
	roomState = state::ENDs;

	Clear();
}

void Room::Update()
{
	if (isPlay() == false)
		return;

	//소멸자 호출 막으려고 포인터 사용함
	vector<Player*> dead;
	for (auto& p : _players)
	{
		p.Update();

		if (p.isDead())
			dead.push_back(&p); // 여기서 깊은 복사 안 일어나서 그런 것 같기도
	}

	for (auto& p : dead)
	{
		p->SendDead(playerCount+1);
	}

	playerCount -= dead.size();

	if (playerCount <= 1) {
		cout << "MakeWinner" << endl;
		roomState = ENDs;
		MakeWinner();
		return;
	}

	DoTimer(50, &Room::Update);
}

void Room::MakeWinner()
{
	Player* winner = nullptr;
	for (auto& p : _players)
	{
		if (p.isDead() == false)
			winner = &p;
	}

	if (winner != nullptr)
		winner->SendWin();

	PlayEnd();
}




