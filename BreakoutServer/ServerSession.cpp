#include "pch.h"
#include "ServerSession.h"
#include "RoomManager.h"
#include "ServerPacketHandler.h"


void ServerSession::OnConnected()
{
	
}

void ServerSession::OnDisconnected()
{
	if(_roomNumber == -1)
		return;

	GRoomManager->DoAsync(&RoomManager::RemovePlayer, static_pointer_cast<ServerSession>(shared_from_this()), _roomNumber);
}

void ServerSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketSessionRef session = GetPacketSessionRef();
	ServerPacketHandler::HandlePacket(session, buffer, len);
	return;
}
