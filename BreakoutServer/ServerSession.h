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

	void LeaveRoom() { _roomNumber = -1; }
	void Clear() { _key = ""; _roomNumber = -1; }

	string _key;
	int32 _roomNumber = -1;
};