#pragma once
#include "Session.h"

class ServerSession : public PacketSession
{
public:

	~ServerSession()
	{
		cout << "~ServerSession" << endl;
	}

	virtual void OnConnected() sealed;
	virtual void OnDisconnected() sealed;
	virtual void OnRecvPacket(BYTE* buffer, int32 len) sealed;
	virtual void OnSend(int32 len) sealed;

	string _key;
	bool _ready = false;
};