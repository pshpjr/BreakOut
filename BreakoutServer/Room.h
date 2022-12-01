#pragma once
#include "pch.h"
#include "Player.h"

#include <random>
class Room : public JobQueue
{
	enum state
	{
		MATCHING,
		READY,
		START,
		ENDs
	};

	enum { MAXPLAYER =99};

public:

	Room(int32 roomNumber) :roomNumber(roomNumber) { _players.resize(MAXPLAYER); }

	void AddSession(GameSessionRef session);
	bool RemoveSession(GameSessionRef session);

	void HandleReady(GameSessionRef session);
	void HandleInput(GameSessionRef session,Protocol::KeyInput input);

	void RoomCheck();
private:
	void Clear();
	bool isFull();
	bool isReady();
	state GetState() { return roomState; }
	bool isPlay() { return (roomState == state::START || roomState == state::READY); }

	void BroadcastState();
	void Broadcast(SendBufferRef buffer);
	void Send(SendBufferRef buffer, GameSessionRef session);

	
	void WaitPlayer();
	void PlayStart();
	void PlayEnd();
	void Update();
	void MakeWinner();

	Player* FindPlayer(GameSessionRef session);

private:
	std::random_device rd;

	int32 roomNumber = 0;
	uint32 playerCount = 0;

	unordered_map<string, int> _keyToIndex;

	Vector<Player> _players;

	state roomState = MATCHING;
	Protocol::S_MOVE movePkt;

};
using RoomRef = shared_ptr<Room>;