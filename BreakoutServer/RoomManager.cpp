#include "pch.h"
#include "RoomManager.h"

RoomManager GRoomManager;

int RoomManager::AddPlayer(GameSessionRef session)
{
	for(int i = 0; i<99;i++)
	{
		if(_rooms[i].isPlay())
			continue;
		if (_rooms[i].Players() < 99) {
			_rooms[i].AddSession(session);
			return i;
		}
	}
	return -1;
}

bool RoomManager::RemovePlayer(GameSessionRef session,int roomNumber)
{
	return _rooms[roomNumber].RemoveSession(session);
}
