#pragma once
#include "ServerSession.h"

class Player : public ServerSession
{
	void clear() { _ready = false; }

public:
	bool _ready = false;
};
 