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
	case S_END:
		Handle_S_END(_session, buffer, len);
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
	if(pkt.players_size() !=99)
	{
		cout << "SOMETHINGWRONG" << endl;
	}
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
		GM->_pongs[target]->_state = Breakout::ALIVE;
		index++;
	}


	Protocol::C_READY pkt2;
	
	pkt2.set_roomnumber(GM->_roomNumber);
	SendBufferRef sendBuffer = MakeSendBuffer(pkt2);
	session->Send(sendBuffer);

	GM->ChangeState(GameReady::instance());
}

void BreakoutPacketHandler::Handle_S_START(ClientSessionRef session, BYTE* buffer, int32 len)
{
	GM->ChangeState(Playing::instance());
}

static uint64 last = 0;
void BreakoutPacketHandler::Handle_S_MOVE(ClientSessionRef session, BYTE* buffer, int32 len)
{
 	Protocol::S_MOVE pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));


	auto input = pkt.inputs();
	for (Protocol::StateU& i : input)
	{
		if(i.code().empty())
			continue;
		int32 index = GM->index[i.code()];

		pt bVec = { i.bvecx(), i.bvecy() };
		GM->_pongs[index]->_b->setVector(bVec);

		pt bLoc = { i.blocx(), i.blocy() };
		GM->_pongs[index]->_b->setLocation(bLoc);

		pt cLoc = { i.clocx(),GM->_pongs[index]->_control_block->getStart().y };
		GM->_pongs[index]->_control_block->setStart(cLoc);

		GM->_pongs[index]->_life = i.life();

		uint64 board = i.boardstate();
		uint64 MSB = static_cast<uint64>(1) << 63;
		for (auto block : GM->_pongs[index]->_blocks)
		{
			bool visible = board & MSB;
			board <<= 1;
			if (visible == 0)
				block->setDead();
			else
				block->setVisible();
		}
	}
}

void BreakoutPacketHandler::Handle_S_END(ClientSessionRef session, BYTE* buffer, int32 len)
{
	cout << "Dead" << endl;
	Protocol::S_END pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	GM->index.clear();

	Dead::instance()->rank = pkt.rank();
	cout << Dead::instance()->rank << endl;
	GM->ChangeState(Dead::instance());
}

