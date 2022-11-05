#pragma once
#include "pch.h"

#include <random>

#include "Room.h"

class ServerSession;

class RoomManager : public JobQueue
{
public:
	RoomManager() { for (int i = 0; i < 100; i++) { _rooms[i] = make_shared<Room>(i); } }
	int AddPlayer(PlayerRef session);
	bool RemovePlayer(PlayerRef session, int roomNumber);
	void Loop();
	RoomRef _rooms[100];
	std::random_device rd;
private:
	USE_LOCK;


};

extern RoomManager GRoomManager;