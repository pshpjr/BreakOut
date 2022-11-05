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
	cout << "Room : " << GM->_roomNumber << endl;
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
	for(auto& i: pkt.players())
	{
		string key = i.code();
		if (key == GM->_key)
		{
			GM->index.insert({ i.code(), 0 });
			index--;
		}
		else
			GM->index.insert({ i.code(),index });

		glm::vec2 startVector = { i.startvector(),1 };
		startVector = glm::normalize(startVector);
		int target = GM->index[key];

		GM->_pongs[target]->_b->setVector(startVector);

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
	Protocol::S_MOVE pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));
	auto tmp = pkt.inputs();
	for(auto& i : tmp)
	{
		int32 index = GM->index[i.code()];

		float speed = i.onoff() ? GM->CONTROLBLOCKSPEED : 0;
		GM->_pongs[index]->_control_block->setSpeed(speed);


		int XVecDirection = i.direction() ? -1 : 1;
		GM->_pongs[index]->_control_block->setVector({ XVecDirection,0 });


	}


}

