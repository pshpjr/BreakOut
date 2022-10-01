#include "pch.h"
#include "ServerSession.h"
#include "GameSessionManager.h"
#include "ServerPacketHandler.h"

void ServerSession::OnConnected()
{
	cout << "connected" << endl;
	GSessionManager.Add(static_pointer_cast<ServerSession>(shared_from_this()));
}

void ServerSession::OnDisconnected()
{
	GSessionManager.Remove(static_pointer_cast<ServerSession>(shared_from_this()));
}

void ServerSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketSessionRef session = GetPacketSessionRef();
	cout << "handle Packet" << endl;
	ServerPacketHandler::HandlePacket(session, buffer, len);

	return;
}

void ServerSession::OnSend(int32 len)
{

}