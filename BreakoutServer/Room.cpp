#include "pch.h"
#include "Room.h"

int Room::AddSession(GameSessionRef session)
{
	WRITE_LOCK;
	_sessions.insert({ session->_key, session });
	if (isFull())
		roomState = READY;
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
	roomState = state::MATCHING;
	for (auto session : _sessions)
	{
		session.second->_ready = false;
	}
	_sessions.clear();
}

bool Room::isFull()
{
	READ_LOCK;
	return _sessions.size() == 99;
}

bool Room::isReady()
{
	if (_sessions.size() == 0)
		return false;

	if (roomState == state::START)
		return false;

	for (auto session : _sessions)
	{
		if (session.second->_ready == false)
			return false;
	}
	return true;
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
