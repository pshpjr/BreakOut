#include "pch.h"
#include "DummySession.h"

#include "BufferReader.h"
#include "DummyPlayer.h"

DummySession::DummySession()
{
	_owner = make_shared<DummyPlayer>();
}

/*
 *
 * DummySession
 *
 */
void DummySession::OnConnected()
{

	Protocol::C_LOGIN pkt;
	pkt.set_usercode(_owner->_key);
	auto sendBuffer = DummyPacketHandler::MakeSendBuffer(pkt);
	Send(sendBuffer);
}

void DummySession::OnSend(int32 len)
{
	PacketSession::OnSend(len);
}

void DummySession::OnDisconnected()
{
	DummySession::OnDisconnected();
}

void DummySession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketSessionRef session = GetPacketSessionRef();
	DummyPacketHandler::HandlePacket(session,buffer, len);
}


/*
 *
 * Dummy Packet Handler
 *
 */
