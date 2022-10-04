#pragma once
#include "pch.h"

class ClientSession : public PacketSession
{
public:
	~ClientSession() override;
protected:

	void OnConnected() override;
	void OnSend(int32 len) override;
	void OnDisconnected() override;
	void OnRecvPacket(BYTE* buffer, int32 len) override;
};
