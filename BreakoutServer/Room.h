#pragma once
#include "pch.h"


class Room : public JobQueue
{


public:
	Room(int32 roomNumber):roomNumber(roomNumber) {  }
	enum state
	{
		MATCHING,
		READY,
		START,
		ENDs
	};

	int AddSession(GameSessionRef session);
	bool RemoveSession(GameSessionRef session);
	
	void Clear();
	bool isFull();
	bool isReady();
	state GetState() { READ_LOCK; return roomState; }

	void AddData(string key, bool dir, bool onOff);
	void BroadcastData();
	//void BroadcastData(Protocol::S_MOVE data);
	void Broadcast(SendBufferRef buffer);
	void Send(SendBufferRef buffer, GameSessionRef session);
	int Players() { READ_LOCK; return playerCount; }
	bool isPlay() {return (roomState == state::START ||roomState ==  state::READY); }
	void WaitPlayer();
	void PlayStart();

	void RoomCheck();


	//unordered_set<GameSessionRef> _sessions;
	unordered_map <string, GameSessionRef> _sessions;
private:
	int32 MAXPLAYER = 99;
	uint32 playerCount = 0;
	int32 roomNumber = 0;

	USE_MANY_LOCKS(2); //1 : sessions 건드림, 2: movePkt, pktIdx 건드림
	state roomState = MATCHING;
	Protocol::S_MOVE movePkt[2] = {};
	int32 pktIdx = 0;
};
using RoomRef = shared_ptr<Room>;