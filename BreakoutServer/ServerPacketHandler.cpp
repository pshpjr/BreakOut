#include "pch.h"
#include "ServerPacketHandler.h"

#include "BufferReader.h"
#include "BufferWriter.h"
#include "ServerSession.h"
#include "Service.h"

void ServerPacketHandler::HandlePacket(PacketSessionRef session, BYTE* buffer, int32 len)
{
	GameSessionRef gameSession = static_pointer_cast<ServerSession>(session);

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

void ServerPacketHandler::Handle_C_LOGIN(GameSessionRef session, BYTE* buffer, int32 len)
{
	Protocol::C_LOGIN pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	session->_key = pkt.usercode();

	cout << "userKEY : " << session->_key << endl;

	Protocol::S_LOGIN loginOk;
	loginOk.set_success(true);
	auto buff = MakeSendBuffer(loginOk);
	session->Send(buff);
}

void ServerPacketHandler::Handle_C_MACHING_GAME(GameSessionRef session, BYTE* buffer, int32 len)
{
	int roomNumber = GRoomManager.AddPlayer(session);

	if (roomNumber < 0)
		cout << "Server is full" << endl;

	Protocol::S_MACHING_GAME pkt;
	pkt.set_roomnumber(roomNumber);
	session->Send(MakeSendBuffer(pkt));

	Room& room = GRoomManager.getRoom(roomNumber);
	
}

void ServerPacketHandler::Handle_C_CANCLE_GAME(GameSessionRef session, BYTE* buffer, int32 len)
{
	Protocol::C_CANCLE_GAME pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	int32 roomNumber = pkt.roomnumber();

	GRoomManager.RemovePlayer(session, roomNumber);
}

void ServerPacketHandler::Handle_C_READY(GameSessionRef session, BYTE* buffer, int32 len)
{
	Protocol::C_READY pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	session->_ready = true;
}

void ServerPacketHandler::Handle_C_MOVE(GameSessionRef session, BYTE* buffer, int32 len)
{
	Protocol::C_MOVE pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	int32 roomN = pkt.roomnumber();

	Protocol::KeyInput* key = new Protocol::KeyInput;

	key->set_direction(pkt.input().direction());
	key->set_onoff(pkt.input().onoff());

	Protocol::S_MOVE pkt2;
	auto send = pkt2.add_inputs();
	send->set_allocated_input(key);
	send->set_code(session->_key);

	auto sBuffer = MakeSendBuffer(pkt2);

	GRoomManager.getRoom(roomN).Broadcast(sBuffer);
}
