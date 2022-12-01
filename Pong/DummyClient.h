#pragma once
#include "pch.h"
class DummyClient;
class DummyService;

extern shared_ptr <DummyClient> DM;

class DummyClient : public JobQueue 
{
public:
	DummyClient(wstring ip, int port,int count);
	void Loop();

	wstring _ip;
	int _port;
	int32 dummyPlayers = 98;
	std::random_device rd;
	
	shared_ptr<DummyService> _service;
};
