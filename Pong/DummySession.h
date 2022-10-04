#pragma once
#include "pch.h"


class DummySession : public PacketSession
{
protected:
	void OnConnected() override;
	void OnSend(int32 len) override;
	void OnDisconnected() override;
	void OnRecvPacket(BYTE* buffer, int32 len) override;

public:
	static SendBufferRef MakeSendBuffer(Protocol::C_LOGIN& pkt) { return _MakeSendBuffer(pkt, C_LOGIN); }
	static SendBufferRef MakeSendBuffer(Protocol::C_MACHING_GAME& pkt) { return _MakeSendBuffer(pkt, C_MACHING_GAME); }
	static SendBufferRef MakeSendBuffer(Protocol::C_CANCLE_GAME& pkt) { return _MakeSendBuffer(pkt, C_CANCLE_GAME); }
	static SendBufferRef MakeSendBuffer(Protocol::C_READY& pkt) { return _MakeSendBuffer(pkt, C_READY); }
	static SendBufferRef MakeSendBuffer(Protocol::C_MOVE& pkt) { return _MakeSendBuffer(pkt, C_MOVE); }

	void HandlePacket(BYTE* buffer, int32 len);
	void Handle_S_LOGIN(BYTE* buffer, int32 len);
	void Handle_S_MACHING_GAME(BYTE* buffer, int32 len);
	void Handle_S_CANCLE_GAME(BYTE* buffer, int32 len);
	void Handle_S_ENTER_GAMET(BYTE* buffer, int32 len);
	void Handle_S_START(BYTE* buffer, int32 len);
	void Handle_S_MOVE(BYTE* buffer, int32 len);

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

		pkt.SerializeToArray(&header[1], dataSize);

		sendBuffer->Close(PacketSize);
		return sendBuffer;
	}

	volatile GameState _state = LOBBY;
};