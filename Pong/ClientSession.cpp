#include "pch.h"
#include "ClientSession.h"

ClientSession::~ClientSession()
{
}

void ClientSession::OnConnected()
{
	Protocol::C_LOGIN pkt;
	cout << "Send Key : "+GM->_key<<endl;
	pkt.set_usercode(GM->_key);
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
	PacketSessionRef session= GetPacketSessionRef();
	BreakoutPacketHandler::HandlePacket(session,buffer, len);
}

