#include "pch.h"
#include "BreakoutPacketHandler.h"

#include "BufferReader.h"

void BreakoutPacketHandler::HandlePacket(BYTE* buffer, int32 len)
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

void BreakoutPacketHandler::Handle_S_LOGIN(BYTE* buffer, int32 len)
{
	Protocol::S_LOGIN pkt;

	cout << pkt.success() << endl;
}

void BreakoutPacketHandler::Handle_S_MACHING_GAME(BYTE* buffer, int32 len)
{
	GM->ChangeState(Matching::instance());
}

void BreakoutPacketHandler::Handle_S_CANCLE_GAME(BYTE* buffer, int32 len)
{
}

void BreakoutPacketHandler::Handle_S_ENTER_GAMET(BYTE* buffer, int32 len)
{
	GM->ChangeState(GameReady::instance());
}

void BreakoutPacketHandler::Handle_S_START(BYTE* buffer, int32 len)
{
	GM->ChangeState(Playing::instance());
}

void BreakoutPacketHandler::Handle_S_MOVE(BYTE* buffer, int32 len)
{
	Protocol::S_MOVE pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	for(auto i : pkt.inputs())
	{
		if (i.input().onoff())
			GM->_mainPlay->_control_block->setSpeed(GM->CONTROLBLOCKSPEED);
		else
			GM->_mainPlay->_control_block->setSpeed(0);

		if (i.input().direction())
			GM->_mainPlay->_control_block->setVector({ -1,0 });
		else
			GM->_mainPlay->_control_block->setVector({ 1,0 });
	}


}
