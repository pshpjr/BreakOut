#include "pch.h"
#include "DummyPacketHandler.h"
#include "DummyPlayer.h"


void DummyPacketHandler::HandlePacket(PacketSessionRef session, BYTE* buffer, int32 len)
{
	DummySessionRef _session = static_pointer_cast<DummySession>(session);

	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	switch (header.id)
	{
	case S_LOGIN:
		Handle_S_LOGIN(_session, buffer, len);
		break;
	case S_MACHING_GAME:
		Handle_S_MACHING_GAME(_session, buffer, len);
		break;
	case S_CANCLE_GAME:
		Handle_S_CANCLE_GAME(_session, buffer, len);
		break;
	case S_ENTER_GAME:
		Handle_S_ENTER_GAME(_session, buffer, len);
		break;
	case S_START:
		Handle_S_START(_session, buffer, len);
		break;
	case S_MOVE:
		Handle_S_MOVE(_session, buffer, len);
		break;
	case S_END:
		Handle_S_END(_session, buffer, len);
		break;
	default:
		CRASH("invalid header id")
	}
}

void DummyPacketHandler::Handle_S_LOGIN(DummySessionRef session, BYTE* buffer, int32 len)
{
	Protocol::S_LOGIN Rpkt;
	Rpkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));
	if (Rpkt.success() == false)
		ASSERT_CRASH("cannot login");

	session->_owner->_state = LOBBY;
}

void DummyPacketHandler::Handle_S_MACHING_GAME(DummySessionRef session, BYTE* buffer, int32 len)
{
	Protocol::S_MACHING_GAME Rpkt;
	Rpkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));
	session->_owner->roomNumber = Rpkt.roomnumber();

	session->_owner->_state = MATCHING;
}

void DummyPacketHandler::Handle_S_CANCLE_GAME(DummySessionRef session, BYTE* buffer, int32 len)
{
}

void DummyPacketHandler::Handle_S_ENTER_GAME(DummySessionRef session, BYTE* buffer, int32 len)
{
	Protocol::S_ENTER_GAME Rpkt;
	Rpkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));
	ASSERT_CRASH(session->_owner->roomNumber == Rpkt.roomnumber());

	session->_owner->_state = GAMEREADY;

	Protocol::C_READY pkt;
	pkt.set_roomnumber(Rpkt.roomnumber());

	SendBufferRef sb = MakeSendBuffer(pkt);
	session->Send(sb);
}

void DummyPacketHandler::Handle_S_START(DummySessionRef session, BYTE* buffer, int32 len)
{
	session->_owner->_state = PLAYING;
}

void DummyPacketHandler::Handle_S_MOVE(DummySessionRef session, BYTE* buffer, int32 len)
{

}

void DummyPacketHandler::Handle_S_END(DummySessionRef session, BYTE* buffer, int32 len)
{
	session->_owner->_state = LOBBY;
}



