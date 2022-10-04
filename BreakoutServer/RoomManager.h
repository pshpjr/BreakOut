#pragma once
#include "pch.h"

#include "Room.h"

class ServerSession;

class RoomManager
{
public:
	RoomManager() { }
	int AddPlayer(GameSessionRef session);
	bool RemovePlayer(GameSessionRef session, int roomNumber);

private:
	Room _rooms[100] = {};
};

extern RoomManager GRoomManager;