#include "pch.h"
#include "ServerPacketHandler.h"
 

#include "BufferReader.h"
#include "BufferWriter.h"
#include "ServerSession.h"
#include "Service.h"

void ServerPacketHandler::HandlePacket(PacketSessionRef session, BYTE* buffer, int32 len)
{
	P_Event()
	ServerSessionRef gameSession = static_pointer_cast<ServerSession>(session);

	BufferReader br(buffer, len);

	PacketHeader header{};

	br >> header;
	
	switch (header.id)
	{
	case C_LOGIN:
		Handle_C_LOGIN(gameSession, buffer, len);
		break;
	case C_MACHING_GAME:
		Handle_C_MACHING_GAME(gameSession, buffer, len);
		break;
	case C_CANCLE_GAME:
		Handle_C_CANCLE_GAME(gameSession, buffer, len);
		break;
	case C_READY:
		Handle_C_READY(gameSession, buffer, len);
		break;
	case C_MOVE:
		Handle_C_MOVE(gameSession, buffer, len);
		break;
	default:
		CRASH("invalid header id")
	}
}

void ServerPacketHandler::Handle_C_LOGIN(ServerSessionRef session, BYTE* buffer, int32 len)
{
	P_Event();
	BYTE data = *buffer;
	Protocol::C_LOGIN pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	session->_owner->_key = pkt.usercode();

	Protocol::S_LOGIN loginOk;
	loginOk.set_success(true);
	auto buff = MakeSendBuffer(loginOk);
	session->Send(buff);
}

void ServerPacketHandler::Handle_C_MACHING_GAME(ServerSessionRef session, BYTE* buffer, int32 len)
{
	P_Event();
	int roomNumber = GRoomManager.AddPlayer(session->_owner);

	if (roomNumber < 0)
		cout << "Server is full" << endl;

	Protocol::S_MACHING_GAME pkt;
	pkt.set_roomnumber(roomNumber);
	session->Send(MakeSendBuffer(pkt));

}

void ServerPacketHandler::Handle_C_CANCLE_GAME(ServerSessionRef session, BYTE* buffer, int32 len)
{
	P_Event();
	Protocol::C_CANCLE_GAME pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	int32 roomNumber = pkt.roomnumber();

	GRoomManager.RemovePlayer(session->_owner, roomNumber);
}

void ServerPacketHandler::Handle_C_READY(ServerSessionRef session, BYTE* buffer, int32 len)
{
	P_Event();
	Protocol::C_READY pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	session->_owner->_ready = true;
}

void ServerPacketHandler::Handle_C_MOVE(ServerSessionRef session, BYTE* buffer, int32 len)
{
		P_Event();
		Protocol::C_MOVE pkt;
		pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

		int32 roomN = pkt.roomnumber();

		auto input = pkt.input();
		bool dir = input.direction();
		bool onOff = input.onoff();

		GRoomManager._rooms[roomN]->DoAsync(&Room::AddData, session->_owner->_key, dir, onOff);
}
