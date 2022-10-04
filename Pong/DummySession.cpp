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
	string key = random_string(KEY_LENGTH);

	Protocol::C_LOGIN pkt;
	pkt.set_usercode(key);
	auto sendBuffer = BreakoutPacketHandler::MakeSendBuffer(pkt);
	Send(sendBuffer);
}

void DummySession::OnDisconnected()
{
	DummySession::OnDisconnected();
}

void DummySession::OnRecvPacket(BYTE* buffer, int32 len)
{
	DummySession::HandlePacket(buffer, len);
}

/*
 *
 * Dummy Packet Handler
 *
 */

void DummySession::HandlePacket(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;

	br >> header;

	switch (header.id)
	{
	case S_LOGIN:
		Handle_S_LOGIN(buffer, len);
		break;
	case S_MACHING_GAME:
		Handle_S_MACHING_GAME(buffer, len);
		break;
	case S_CANCLE_GAME:
		Handle_S_CANCLE_GAME(buffer, len);
		break;
	case S_ENTER_GAME:
		Handle_S_ENTER_GAMET(buffer, len);
		break;
	case S_START:
		Handle_S_START(buffer, len);
		break;
	case S_MOVE:
		Handle_S_MOVE(buffer, len);
		break;
	default:
		CRASH("invalid header id")
	}
}

void DummySession::Handle_S_LOGIN(BYTE* buffer, int32 len)
{
	this_thread::sleep_for(1s);
	GM->ChangeState(Lobby::instance());
}

void DummySession::Handle_S_MACHING_GAME(BYTE* buffer, int32 len)
{
	_state = MATCHING;
	Protocol::C_MACHING_GAME pkt;
	SendBufferRef s=  MakeSendBuffer(pkt);
	GM->ChangeState(Matching::instance());
	this->Send(s);

}

void DummySession::Handle_S_CANCLE_GAME(BYTE* buffer, int32 len)
{
	_state = LOBBY;
}

void DummySession::Handle_S_ENTER_GAMET(BYTE* buffer, int32 len)
{
	_state = GAMEREADY;
	GM->ChangeState(Playing::instance());
}

void DummySession::Handle_S_START(BYTE* buffer, int32 len)
{
	_state = PLAYING;
	bool direction = true;

	while(_state == PLAYING)
	{
		Protocol::KeyInput* key = new Protocol::KeyInput;
		Protocol::C_MOVE pkt;

		key->set_direction(direction);
		key->set_onoff(true);

		pkt.set_allocated_input(key);

		SendBufferRef buffer = BreakoutPacketHandler::MakeSendBuffer(pkt);

		this->Send(buffer);

		this_thread::sleep_for(1s);

		key->set_direction(direction);
		key->set_onoff(false);

		pkt.set_allocated_input(key);

		SendBufferRef buffer2 = BreakoutPacketHandler::MakeSendBuffer(pkt);

		this->Send(buffer2);

		direction = !direction;
		this_thread::sleep_for(2s);
	}
}

void DummySession::Handle_S_MOVE(BYTE* buffer, int32 len)
{
	Protocol::S_MOVE pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

}
