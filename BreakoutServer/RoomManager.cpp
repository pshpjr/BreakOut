#include "pch.h"
#include "RoomManager.h"

#include "GlobalQueue.h"
#include "Protocol.pb.h"
#include "ServerPacketHandler.h"

shared_ptr<RoomManager> GRoomManager = MakeShared<RoomManager>();

void RoomManager::Init()
{
	int t = 0;
	for (auto& i :_rooms)
	{
		i->DoTimer(t, &Room::RoomCheck);
		t += 15;
	}
}

void RoomManager::AddPlayer(GameSessionRef session, int roomNumber)
{
	lastRoom = roomNumber;
	_rooms[lastRoom]->DoAsync(&Room::AddSession, session);
}

void RoomManager::RemovePlayer(GameSessionRef session,int roomNumber)
{
	_rooms[roomNumber]->DoAsync(&Room::RemoveSession, session);
}

void RoomManager::HandleReady(GameSessionRef session, int roomNumber)
{

	_rooms[roomNumber]->DoAsync(&Room::HandleReady, session);
}

void RoomManager::HandleInput(GameSessionRef session, int roomNumber, Protocol::KeyInput input)
{
	_rooms[roomNumber]->DoAsync(&Room::HandleInput, session,input);
}


