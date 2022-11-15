#pragma once
#include "BufferReader.h"
#include "BufferWriter.h"
#include "RoomManager.h"
#include "Protocol.pb.h"
//S_ : 서버로 보내는
//C_ : 클라로 보내는

inline int Count = 0;

enum PACKET_TYPE: uint16
{
	C_LOGIN,
	S_LOGIN,
	C_MACHING_GAME,
	S_MACHING_GAME,
	C_CANCLE_GAME,
	S_CANCLE_GAME,
	S_ENTER_GAME,
	C_READY,
	S_START,
	C_MOVE,
	S_MOVE,
	S_END
};
inline vector<string> PACKET_TYPE_STR = { "C_LOGIN", "S_LOGIN",
	"C_MACHING_GAME",
	"S_MACHING_GAME",
	"C_CANCLE_GAME",
	"S_CANCLE_GAME",
	"S_ENTER_GAME",
	"C_READY",
	"S_START",
	"C_MOVE",
	"S_MOVE" };
class ServerPacketHandler
{
public:

	static void HandlePacket(PacketSessionRef session, BYTE* buffer, int32 len);

	static SendBufferRef MakeSendBuffer(Protocol::S_LOGIN& pkt) { return _MakeSendBuffer(pkt, S_LOGIN); }
	static SendBufferRef MakeSendBuffer(Protocol::S_MACHING_GAME& pkt) { return _MakeSendBuffer(pkt, S_MACHING_GAME); }
	static SendBufferRef MakeSendBuffer(Protocol::S_CANCLE_GAME& pkt) { return _MakeSendBuffer(pkt, S_CANCLE_GAME); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ENTER_GAME& pkt) { return _MakeSendBuffer(pkt, S_ENTER_GAME); }
	static SendBufferRef MakeSendBuffer(Protocol::S_START& pkt) { return _MakeSendBuffer(pkt, S_START); }
	static SendBufferRef MakeSendBuffer(Protocol::S_MOVE& pkt) { return _MakeSendBuffer(pkt, S_MOVE); }
	static SendBufferRef MakeSendBuffer(Protocol::S_END& pkt) { return _MakeSendBuffer(pkt, S_END); }

	static void Handle_C_LOGIN(GameSessionRef session, BYTE* buffer, int32 len);
	static void Handle_C_MACHING_GAME(GameSessionRef session, BYTE* buffer, int32 len);
	static void Handle_C_CANCLE_GAME(GameSessionRef session, BYTE* buffer, int32 len);
	static void Handle_C_READY(GameSessionRef session, BYTE* buffer, int32 len);
	static void Handle_C_MOVE(GameSessionRef session, BYTE* buffer, int32 len);

private:

	template <typename T>
	static SendBufferRef _MakeSendBuffer(T& pkt, uint16 pktid)
	{
		const uint16 dataSize = static_cast<uint16> (pkt.ByteSizeLong());
		const uint16 PacketSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = GSendBufferManager->Open(PacketSize);

		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = PacketSize;
		header->id = pktid;

		ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));

		sendBuffer->Close(PacketSize);
		return sendBuffer;
	}
};
