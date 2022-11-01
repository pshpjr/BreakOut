#include "pch.h"
#include "RoomManager.h"

#include "GlobalQueue.h"
#include "Protocol.pb.h"
#include "ServerPacketHandler.h"

RoomManager GRoomManager;

int RoomManager::AddPlayer(GameSessionRef session)
{
	WRITE_LOCK;
	for(int i = 0; i<100;i++)
	{
		if(_rooms[i]->isPlay())
			continue;
		if (_rooms[i]->isFull() == false)
		{
			_rooms[i]->AddSession(session);
			return i;
		}


	}
	
	return -1;
}

bool RoomManager::RemovePlayer(GameSessionRef session,int roomNumber)
{
	WRITE_LOCK;
	return _rooms[roomNumber]->RemoveSession(session);
	return true;
}


