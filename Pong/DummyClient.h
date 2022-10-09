﻿#pragma once
#include "pch.h"
class DummyService;

class DummyClient
{
public:
	DummyClient(wstring ip, int port,int count);
	void Loop();

	wstring _ip;
	int _port;
	int32 dummyPlayers = 98;

	shared_ptr<DummyService> _service;
};
