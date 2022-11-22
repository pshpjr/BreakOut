#pragma once
#include "pch.h"


#include "Room.h"

class ServerSession;

class RoomManager : public JobQueue
{
public:
	RoomManager() { for (int i = 0; i < 401; i++) { _rooms[i] = make_shared<Room>(i); } }

	void Init();

	void AddPlayer(GameSessionRef session,int roomNumber = 0);
	void RemovePlayer(GameSessionRef session, int roomNumber);

	void HandleReady(GameSessionRef session, int roomNumber);
	void HandleInput(GameSessionRef session, int roomNumber, Protocol::KeyInput input);


private:
	RoomRef _rooms[401];
	int32 lastRoom = 0;
};

extern shared_ptr<RoomManager> GRoomManager;