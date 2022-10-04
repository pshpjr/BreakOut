#pragma once
#include "pch.h"

class Room
{
public:
	Room() = default;

	int AddSession(GameSessionRef session);
	bool RemoveSession(GameSessionRef key);
	
	void Clear();
	bool isFull();
	void Broadcast(SendBufferRef buffer);
	void Send(SendBufferRef buffer, GameSessionRef session);
	int Players() { READ_LOCK; return _sessions.size(); }
	bool isPlay() {return _isPlaying; }
	void PlayStart() { READ_LOCK; _isPlaying = true; }

private:
	USE_LOCK;
	bool _isPlaying = false;
	unordered_map <string,GameSessionRef> _sessions;
};
