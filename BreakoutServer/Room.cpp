#include "pch.h"
#include "Room.h"

int Room::AddSession(GameSessionRef session)
{
	WRITE_LOCK;
	_sessions.insert({ session->_key, session });
	if (isFull())
		_isPlaying = true;
	return true;
}

bool Room::RemoveSession(GameSessionRef session)
{
	WRITE_LOCK;
	return _sessions.erase(session->_key);
}

void Room::Clear()
{
	WRITE_LOCK;
	_sessions.clear();
}

bool Room::isFull()
{
	READ_LOCK;
	return _sessions.size() == 99;
}

void Room::Broadcast(SendBufferRef buffer)
{
	for(auto session : _sessions)
	{
		session.second->Send(buffer);
	}
}

void Room::Send(SendBufferRef buffer, GameSessionRef session)
{
	session->Send(buffer);
}
