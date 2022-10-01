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
		cout << "handle Login" << endl;
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

	cout << session->_key << endl;

	Protocol::S_LOGIN loginOk;
	loginOk.set_success(true);
	auto buff = MakeSendBuffer(loginOk);
	session->Send(buff);
}

void ServerPacketHandler::Handle_C_MACHING_GAME(GameSessionRef session, BYTE* buffer, int32 len)
{
	Protocol::S_MACHING_GAME pkt;
	pkt.set_roomnumber(1);
	session->Send(MakeSendBuffer(pkt));

	Protocol::S_ENTER_GAME pkt2;
	pkt2.set_roomnumber(1);
	pkt2.set_success(true);

	session->Send(MakeSendBuffer(pkt2));

	this_thread::sleep_for(1s);

	Protocol::S_START pkt3;
	session->Send(MakeSendBuffer(pkt3));
}

void ServerPacketHandler::Handle_C_CANCLE_GAME(GameSessionRef session, BYTE* buffer, int32 len)
{
}

void ServerPacketHandler::Handle_C_READY(GameSessionRef session, BYTE* buffer, int32 len)
{
}

void ServerPacketHandler::Handle_C_MOVE(GameSessionRef session, BYTE* buffer, int32 len)
{
	Protocol::C_MOVE pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	Protocol::KeyInput* key = new Protocol::KeyInput;

	key->set_direction(pkt.input().direction());
	key->set_onoff(pkt.input().onoff());

	Protocol::S_MOVE pkt2;
	auto send = pkt2.add_inputs();
	send->set_allocated_input(key);
	send->set_userid(1);
	auto sBuffer = MakeSendBuffer(pkt2);
	session->GetService()->Broadcast(sBuffer);
}
