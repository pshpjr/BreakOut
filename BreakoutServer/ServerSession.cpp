#include "pch.h"
#include "ServerSession.h"
#include "RoomManager.h"
#include "ServerPacketHandler.h"

void ServerSession::OnConnected()
{
	
}

void ServerSession::OnDisconnected()
{
	
}

void ServerSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketSessionRef session = GetPacketSessionRef();
	ServerPacketHandler::HandlePacket(session, buffer, len);
	return;
}

void ServerSession::OnSend(int32 len)
{


}