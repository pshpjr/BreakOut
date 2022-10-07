#pragma once
#include "pch.h"
class DummyClient
{
public:
	DummyClient(wstring ip, int port);
	void Loop();

	wstring _ip;
	int _port;

	ClientServiceRef _service;
	set<SessionRef> _sessions;
};
