#include "pch.h"
#include "RoomManager.h"

#include "Protocol.pb.h"
#include "ServerPacketHandler.h"

RoomManager GRoomManager;

//락 안잡아서 문제 생길 수 있음
int RoomManager::AddPlayer(GameSessionRef session)
{
	for(int i = 0; i<99;i++)
	{
		if(_rooms[i].isPlay())
			continue;
		if (_rooms[i].isFull() == false)
		{
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

void RoomManager::Loop()
{
	for (int i = 0; i < 99; i++)
	{
		if (_rooms[i].isFull() && !_rooms->isPlay())
		{
			_rooms[i].WaitPlayer();

			Protocol::S_ENTER_GAME pkt;


			for(auto session : _rooms[i]._sessions)
			{
				auto a = pkt.add_players();
				a->set_code(session.second->_key);
				a->set_name("Test");
			}
			
			pkt.set_roomnumber(i);
			pkt.set_success(true);

			_rooms[i].Broadcast(ServerPacketHandler::MakeSendBuffer(pkt));
		}

		if(_rooms[i].isReady())
		{
			cout << "Room " + std::to_string(i) + " start" << endl;
			_rooms[i].PlayStart();

			Protocol::S_START pkt;
			_rooms[i].Broadcast(ServerPacketHandler::MakeSendBuffer(pkt));
		}
	}
}
