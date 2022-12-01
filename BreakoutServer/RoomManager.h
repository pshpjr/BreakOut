#pragma once
#include "pch.h"


#include "Room.h"



class ServerSession;

class RoomManager : public JobQueue
{
public:
	RoomManager() { for (int i = 0; i < maxRoom; i++) { _rooms[i] = make_shared<Room>(i); } }

	void Init();
	void AddPlayer(GameSessionRef session);
	void AddPlayer(GameSessionRef session,int roomNumber);
	void RemovePlayer(GameSessionRef session, int roomNumber);

	void HandleReady(GameSessionRef session, int roomNumber);
	void HandleInput(GameSessionRef session, int roomNumber, Protocol::KeyInput input);


private:
	static const int32 maxRoom = 401;
	RoomRef _rooms[maxRoom];
	int32 lastRoom = 0;
};

extern shared_ptr<RoomManager> GRoomManager;
