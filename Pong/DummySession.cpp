#include "pch.h"
#include "DummySession.h"

#include "BufferReader.h"

/*
 *
 * DummySession
 *
 */
void DummySession::OnConnected()
{
	cout << "ClientOnConnect" << endl;
	string key = random_string(KEY_LENGTH);

	Protocol::C_LOGIN pkt;
	pkt.set_usercode(key);
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
