#pragma once
#include "pch.h"

class Room
{
	enum state
	{
		MATCHING,
		READY,
		START
	} ;

public:

	int AddSession(GameSessionRef session);
	bool RemoveSession(GameSessionRef key);
	
	void Clear();
	bool isFull();
	bool isReady();
	void Broadcast(SendBufferRef buffer);
	void Send(SendBufferRef buffer, GameSessionRef session);
	int Players() { READ_LOCK; return _sessions.size(); }
	bool isPlay() {return roomState == state::START; }
	void WaitPlayer() {roomState = READY;}
	void PlayStart() { READ_LOCK; roomState = state::START; }


	USE_LOCK;
	state roomState = state::MATCHING;

	unordered_map <string,GameSessionRef> _sessions;
};
