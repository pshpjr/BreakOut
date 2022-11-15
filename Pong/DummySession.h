#pragma once
#include "pch.h"


class DummyPlayer;

class DummySession : public PacketSession
{
public:
	DummySession();

	void OnConnected() override;
	void OnSend(int32 len) override;
	void OnDisconnected() override;
	void OnRecvPacket(BYTE* buffer, int32 len) override;

	shared_ptr<DummyPlayer> _owner;
};
