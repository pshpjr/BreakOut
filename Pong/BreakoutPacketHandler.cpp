#include "pch.h"
#include "BreakoutPacketHandler.h"

#include "BufferReader.h"


void BreakoutPacketHandler::HandlePacket(PacketSessionRef session, BYTE* buffer, int32 len)
{
	ClientSessionRef _session = static_pointer_cast<ClientSession>(session);

	BufferReader br(buffer, len);

	PacketHeader header;

	br >> header;

	switch (header.id)
	{
	case S_LOGIN:
		Handle_S_LOGIN(_session,buffer, len);
		break;
	case S_MACHING_GAME:
		Handle_S_MACHING_GAME(_session, buffer, len);
		break;
	case S_CANCLE_GAME:
		Handle_S_CANCLE_GAME(_session, buffer, len);
		break;
	case S_ENTER_GAME:
		Handle_S_ENTER_GAMET(_session, buffer, len);
		break;
	case S_START:
		Handle_S_START(_session, buffer, len);
		break;
	case S_MOVE:
		Handle_S_MOVE(_session, buffer, len);
		break;
	default:
		CRASH("invalid header id")
	}
}

void BreakoutPacketHandler::Handle_S_LOGIN(ClientSessionRef session, BYTE* buffer, int32 len)
{
	GM->ChangeState(Lobby::instance());
}

void BreakoutPacketHandler::Handle_S_MACHING_GAME(ClientSessionRef session, BYTE* buffer, int32 len)
{
	Protocol::S_MACHING_GAME pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	GM->_roomNumber = pkt.roomnumber();

	GM->ChangeState(Matching::instance());
}

void BreakoutPacketHandler::Handle_S_CANCLE_GAME(ClientSessionRef session, BYTE* buffer, int32 len)
{

	GM->ChangeState(Lobby::instance());
}

void BreakoutPacketHandler::Handle_S_ENTER_GAMET(ClientSessionRef session, BYTE* buffer, int32 len)
{
	Protocol::S_ENTER_GAME pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	if(pkt.roomnumber() != GM->_roomNumber){
		return;
	}

	int index = 1;
	for(auto i: pkt.players())
	{
		if (i.code() == GM->_key)
		{
			GM->index.insert({ i.code(), 0 });
			continue;
		}

		GM->index.insert({ i.code(),index });
		index++;
	}
	
	Protocol::C_READY pkt2;
	SendBufferRef sendBuffer = MakeSendBuffer(pkt2);
	session->Send(sendBuffer);

	GM->ChangeState(GameReady::instance());
}

void BreakoutPacketHandler::Handle_S_START(ClientSessionRef session, BYTE* buffer, int32 len)
{
	GM->ChangeState(Playing::instance());
}

void BreakoutPacketHandler::Handle_S_MOVE(ClientSessionRef session, BYTE* buffer, int32 len)
{
	cout << "handle Move" << endl;
	Protocol::S_MOVE pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));
	auto tmp = pkt.inputs();
	for(auto& i : tmp)
	{
		int32 index = GM->index[i.code()];
		if (i.onoff())
			GM->_pongs[index]->_control_block->setSpeed(GM->CONTROLBLOCKSPEED);
		else
			GM->_pongs[index]->_control_block->setSpeed(0);

		if (i.direction())
			GM->_pongs[index]->_control_block->setVector({ -1,0 });
		else
			GM->_pongs[index]->_control_block->setVector({ 1,0 });
	}


}

