#include "pch.h"
#include "Room.h"

#include <random>

#include "GlobalQueue.h"
#include "Player.h"
#include "ServerPacketHandler.h"

void Room::AddSession(GameSessionRef session)
{
	if (roomState == state::MATCHING && playerCount < MAXPLAYER)
	{
		ASSERT_CRASH(playerCount < MAXPLAYER);
		_players[playerCount].SetSession(session);
		session->_roomNumber = roomNumber;
		++playerCount;
		Protocol::S_MACHING_GAME pkt;
		pkt.set_roomnumber(roomNumber);
		session->Send(ServerPacketHandler::MakeSendBuffer(pkt));
		return;
	}

	if (roomNumber == 400)
	{
		cout << "server Is Full" << endl;
		return;
	}
	GRoomManager->DoAsync(&RoomManager::AddPlayer, session, roomNumber + 1);
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
		--playerCount;
		ASSERT_CRASH(playerCount >= 0);
	}

	return true;
}

void Room::HandleReady(GameSessionRef session)
{
	if (isPlay() == false)
		session->Disconnect(L"Wrong Room Ready");

	if (session->_roomNumber != roomNumber || roomNumber == -1)
	{
		cout << "WRONG_ROOM_READY | session : " << session->_roomNumber << "packet : " << roomNumber << endl;
		return;
	}


	auto player = FindPlayer(session);
	if (player == nullptr)
		return;

	player->SetReadyTrue();
}

void Room::HandleInput(GameSessionRef session, Protocol::KeyInput input)
{
	if (session->_roomNumber != roomNumber || roomNumber == -1)
	{
		return;
	}

	auto player = FindPlayer(session);
	if (player == nullptr)
		return;

	player->HandleInput(input);
}

void Room::Clear()
{
	ASSERT_CRASH(_players.size() == MAXPLAYER)
	for (auto& p : _players)
	{
		p.ResetBreakout();
		p.ClearSession();
		p.ClearReady();
	}

	playerCount = 0;

	DoTimer(4000, [this]()
		{
			roomState = state::MATCHING;
			DoTimer(200, &Room::RoomCheck);
		});
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

void Room::BroadcastState()
{
	if (isPlay() == false)
		return;
	for (auto& p : _players)
	{
		auto input = movePkt.add_inputs();

		p.SetState(input);
	}
	Broadcast(ServerPacketHandler::MakeSendBuffer(movePkt));
	movePkt.Clear();

	DoTimer(300, &Room::BroadcastState);
}

void Room::Broadcast(SendBufferRef buffer)
{
	P_Event();
	for(auto& p : _players)
	{
		p.Send(buffer);
	}
}

void Room::Send(SendBufferRef buffer, GameSessionRef session)
{
	session->Send(buffer);
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
	roomState = READY;

	Protocol::S_ENTER_GAME pkt;
	pkt.set_roomnumber(roomNumber);
	pkt.set_success(true);

	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-1, 1);

	for (auto& p : _players)
	{
		auto a = pkt.add_players();
		a->set_code(p.GetKey());
		a->set_name("Test");
		float data = dis(gen);
		a->set_startvector(data);
		p.Init(data);
	}


	Broadcast(ServerPacketHandler::MakeSendBuffer(pkt));
}

void Room::PlayStart()
{
	roomState = state::START;

	Protocol::S_START pkt;
	Broadcast(ServerPacketHandler::MakeSendBuffer(pkt));


	Update();
	BroadcastState();
	//DoTimer(100, &Room::BroadcastState);
}

void Room::PlayEnd()
{
	Clear();
	cout << "PlayEnd : "<<roomNumber << endl;
	roomState = state::ENDs;


}


void Room::Update()
{
	if (isPlay() == false)
		return;

	auto start = psh::GetTickCount();

	//소멸자 호출 막으려고 포인터 사용함
	vector<Player*> dead;
	vector<Player*> toBroadcastPlayer;


	for (auto& p : _players)
	{
		if (p.isReady() == false)
			continue;

		bool needBroadcast = false;
		needBroadcast = p.Update();

	}
	for (auto& p : _players)
	{
		if (p.isReady() == false)
			continue;

		bool needBroadcast = false;
		needBroadcast = p.Update();

	}
	for (auto& p : _players)
	{
		if (p.isReady() == false)
			continue;

		bool needBroadcast = false;
		needBroadcast = p.Update();

	}
	for (auto& p : _players)
	{
		if (p.isReady() == false)
			continue;

		bool needBroadcast = false;
		needBroadcast = p.Update();

	}
	for (auto& p : _players)
	{
		if (p.isReady() == false)
			continue;

		bool needBroadcast = false;
		needBroadcast = p.Update();

		if (p.isDead()) {
			dead.push_back(&p);
			continue;
		}
		if (needBroadcast) {
			toBroadcastPlayer.push_back(&p);
		}
	}

	if (dead.size() != 0)
	{
		for (auto& p : dead)
		{
			p->SendDead(playerCount);
			p->ClearReady();
			p->ClearSession();
		}
	}


	//for (auto& p : toBroadcastPlayer)
	//{
	//	auto input = movePkt.add_inputs();

	//	p->SetState(input);
	//}
	//Broadcast(ServerPacketHandler::MakeSendBuffer(movePkt));
	//movePkt.Clear();

	playerCount -= dead.size();

	if (playerCount <= 1) {
		roomState = ENDs;
		MakeWinner();
		return;
	}
	ASSERT_CRASH(playerCount > 0);
	auto end = psh::GetTickCount();
	auto gap = end - start;
	wrap(gap, (uint64)0, (uint64)100);
	DoTimer(100 - gap, &Room::Update);
}

void Room::MakeWinner()
{
	Player* winner = nullptr;
	int winnerCount = 0;
	for (auto& p : _players)
	{
		if (p.isDead() == false)
		{
			winner = &p;
			++winnerCount;
		}
			
	}
	if (winnerCount > 1)
		cout << "&&&&&&&room : " << roomNumber <<" "<< winnerCount << endl;
	if (winner != nullptr)
		winner->SendWin();

	PlayEnd();
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