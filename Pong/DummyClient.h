#pragma once
#include "pch.h"
class DummyClient
{
public:
	DummyClient(wstring ip, int port,int count);
	void Loop();

	wstring _ip;
	int _port;
	int32 dummyPlayers = 98;

	ClientServiceRef _service;
	set<SessionRef> _sessions;
};
