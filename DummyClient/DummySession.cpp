#include "pch.h"
#include "DummySession.h"
#include "ClientPacketHandler.h"

void DummySession::OnConnected()
{
	Protocol::C_LOGIN pkt;
	pkt.set_usercode("1234");

	cout << "send usercode" << endl;
	auto login = ClientPacketHandler::MakeSendBuffer(pkt);
	Send(login);

	PacketSession::OnConnected();
}

void DummySession::OnDisconnected()
{
	PacketSession::OnDisconnected();
}

void DummySession::OnRecvPacket(BYTE* buffer, int32 len)
{
	ClientPacketHandler::HandlePacket(buffer, len);
}

void DummySession::OnSend(int32 len)
{
	PacketSession::OnSend(len);
}
