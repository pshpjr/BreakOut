#pragma once
#include "pch.h"


class DummySession : public PacketSession
{
public:
	void OnConnected() override;
	void OnSend(int32 len) override;
	void OnDisconnected() override;
	void OnRecvPacket(BYTE* buffer, int32 len) override;

	volatile GameState _state = INIT;
	int32 roomNumber = -1;

	bool onOff = true;

};