#include "pch.h"
#include "ClientSession.h"

ClientSession::~ClientSession()
{
}

void ClientSession::OnConnected()
{
	string key = GetKey();
	Protocol::C_LOGIN pkt;
	pkt.set_usercode(key);
	auto sendBuffer = BreakoutPacketHandler::MakeSendBuffer(pkt);
	Send(sendBuffer);
}

void ClientSession::OnSend(int32 len)
{
	
}

void ClientSession::OnDisconnected()
{
	PacketSession::OnDisconnected();
}

void ClientSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	BreakoutPacketHandler::HandlePacket(buffer, len);
}

