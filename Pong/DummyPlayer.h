﻿#pragma once
#include "pch.h"
class DummyPlayer
{
public:
	DummyPlayer() { _key = random_string(KEY_LENGTH); }

	string _key;
	volatile GameState _state = INIT;
	int32 roomNumber = -1;
	int32 endCount = 0;

	bool onOff = true;
};
