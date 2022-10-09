#pragma once
#include "pch.h"

#include "Room.h"

class ServerSession;

class RoomManager
{
public:
	RoomManager() { for (int i = 0; i < 100; i++) { _rooms[i] = make_shared<Room>(i); } }
	int AddPlayer(GameSessionRef session);
	bool RemovePlayer(GameSessionRef session, int roomNumber);
	void Loop();
	RoomRef _rooms[100];

private:
	USE_LOCK;
};

extern RoomManager GRoomManager;