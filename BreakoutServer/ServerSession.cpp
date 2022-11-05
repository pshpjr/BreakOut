#include "pch.h"
#include "ServerSession.h"

#include "Player.h"
#include "RoomManager.h"
#include "ServerPacketHandler.h"


void ServerSession::OnConnected()
{
	_owner = make_shared<Player>(shared_from_this());
}

void ServerSession::OnDisconnected()
{
	_owner->clear();
	_owner = nullptr;
}

void ServerSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketSessionRef session = GetPacketSessionRef();
	ServerPacketHandler::HandlePacket(session, buffer, len);
	return;
}
