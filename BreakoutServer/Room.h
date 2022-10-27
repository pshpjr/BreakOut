#pragma once
#include "pch.h"


class Room
{


public:
	Room(int32 roomNumber):roomNumber(roomNumber) {  }
	enum state
	{
		MATCHING,
		READY,
		START
	};

	int AddSession(GameSessionRef session);
	//bool RemoveSession(GameSessionRef key);
	
	void Clear();
	bool isFull();
	bool isReady();
	state GetState() { READ_LOCK; return roomState; }

	void Broadcast(Protocol::S_MOVE data);
	void Broadcast(SendBufferRef buffer);
	void Send(SendBufferRef buffer, GameSessionRef session);
	int Players() { READ_LOCK; return playerCount; }
	bool isPlay() {return (roomState == state::START ||roomState ==  state::READY); }
	void WaitPlayer();
	void PlayStart();

	unordered_set<GameSessionRef> _sessions;
	//unordered_map <string, GameSessionRef> _sessions;
private:
	int32 MAXPLAYER = 99;
	uint32 playerCount = 0;
	int32 roomNumber = 0;

	USE_LOCK;
	state roomState = MATCHING;
};
using RoomRef = shared_ptr<Room>;