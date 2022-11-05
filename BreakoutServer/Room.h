#pragma once
#include "pch.h"


class Room : public JobQueue
{
	//TODO: 승자 판정 후 나간 Player들은 소멸자 호출되는지 확인

public:
	Room(int32 roomNumber):roomNumber(roomNumber) {  }
	enum state
	{
		MATCHING,
		WAIT_PLAYER,
		PLAYING,
		ENDs
	};

	int AddPlayer(PlayerRef player);
	bool RemovePlayer(PlayerRef player);
	
	void Clear();
	bool isFull();
	bool isReady();
	state GetState() { READ_LOCK; return roomState; }

	void AddData(string key, bool dir, bool onOff);
	void BroadcastData();
	//void BroadcastData(Protocol::S_MOVE data);
	void Broadcast(SendBufferRef buffer);
	void Send(SendBufferRef buffer, PlayerRef session);
	int PlayersCount() { READ_LOCK; return playerCount; }
	bool isPlay() {return (roomState == state::PLAYING ||roomState ==  state::WAIT_PLAYER); }
	void WaitPlayer();
	void PlayStart();

	void RoomCheck();


	//unordered_set<ServerSessionRef> _sessions;
	unordered_set <PlayerRef> _players;
private:
	int32 MAXPLAYER = 99;
	uint32 playerCount = 0;
	int32 roomNumber = 0;

	USE_MANY_LOCKS(2); //0 : sessions 건드림, 1: movePkt, pktIdx 건드림
	state roomState = state::MATCHING;
	Protocol::S_MOVE movePkt[2] = {};
	int32 pktIdx = 0;
};
using RoomRef = shared_ptr<Room>;