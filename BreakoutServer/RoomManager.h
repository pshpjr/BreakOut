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
	void Loop();
	Room& getRoom(int n) { return _rooms[n]; }
private:
	Room _rooms[100] = {};
};

extern RoomManager GRoomManager;