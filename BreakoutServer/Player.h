#pragma once
#include "Macro.h"
#include "ServerSession.h"

struct vec
{
	float x;
	float y;
};

struct PlayerState
{
	int life = 0;
	vec ballVec = {};
	vec ballLoc = {};
	vec CBLoc = {};

};

class Player : public ServerSession
{
public:
	Player(IocpObjectRef ref) { _session = static_pointer_cast<ServerSession>(ref); _connected = true; }
	~Player() { cout << "~player" << endl; }

	void LeaveRoom() { _ready = false; _roomNumber = -1; _state = {}; }
	void clear() { _ready = false; _state = {}; _session = nullptr; _connected = false; }
	void Send(SendBufferRef buffer) const;
	bool isReady() { return _ready; }
	bool isAlive() { return _state.life > 0;}

public:
	bool _connected = false;
	PlayerState _state = {};


	string _key;
	ServerSessionRef _session = nullptr;

	bool _ready = false;
	int _roomNumber = -1;
};
 