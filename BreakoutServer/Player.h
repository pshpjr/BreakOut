#pragma once
#include "pch.h"
#include "Breakout.h"
class Player
{
public:

	void SetSession(ServerSessionRef session) { _session = session; }
	void ClearSession() { if (_session == nullptr) return ;  _session->LeaveRoom();  _session = nullptr; }
	void ClearReady() { _ready = false; }
	void SetReadyTrue() { if (_ready) std::cout << "already True" << endl; _ready = true; }
	bool isReady() { return _ready; }
	string GetKey() { return _session->_key; }
	bool isDead() { return _breakout.isDead(); }
	void setDead() { _breakout.SetDead(); }


	void Send(SendBufferRef buffer) { if (_session == nullptr) return;  _session->Send(buffer); }
	void Update();
	void ResetBreakout();
	void HandleInput(Protocol::KeyInput input);

	void SendDead(int32 rank);
	void SendWin();
	


	bool isEqualSession(ServerSessionRef other) { return other == _session; }
private:
	Breakout _breakout;
	ServerSessionRef _session;

	bool _ready = false;
};
