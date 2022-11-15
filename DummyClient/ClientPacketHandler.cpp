#include "pch.h"
#include "ClientPacketHandler.h"

#include "BufferReader.h"
#include "Protocol.pb.h"

void ClientPacketHandler::HandlePacket(BYTE* buffer, int32 len)
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

void ClientPacketHandler::Handle_S_LOGIN(BYTE* buffer, int32 len)
{
	Protocol::S_LOGIN pkt;

	cout << pkt.success() << endl;
}

void ClientPacketHandler::Handle_S_MACHING_GAME(BYTE* buffer, int32 len)
{
}

void ClientPacketHandler::Handle_S_CANCLE_GAME(BYTE* buffer, int32 len)
{

}

void ClientPacketHandler::Handle_S_ENTER_GAMET(BYTE* buffer, int32 len)
{
}

void ClientPacketHandler::Handle_S_START(BYTE* buffer, int32 len)
{
}

void ClientPacketHandler::Handle_S_MOVE(BYTE* buffer, int32 len)
{
}

