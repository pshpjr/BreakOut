#pragma once
#include "Protocol.pb.h"

class UIState;
class Client
{
public:

	Client(int32 SCREENWIDHT, int32 SCREENHEIGHT,wstring ip, int port);
	void AddPong(int32 width, int32 height, int32 x, int32 y);


	bool Tick();
	bool Update();
	bool Render();

	
	bool InitService();
	void Start();
	void End();

	void noGUI(bool value);
	void AddPong(int32 width, int32 height, int32 x, int32 y, char L, char R);

	bool ProcessInput(float dt);
	void ChangeState(UIState* state) { _state = state; }

	//벡터에 값을 넣음 -> 벡터 확장 -> 이동/복사 해야 함 -> 소멸자 호출
	unique_ptr<Protocol::S_MOVE> pkt;

	vector<BreakoutPtr> _pongs;
	BreakoutPtr _mainPlay;
	bool _noGUI = false;
	bool Keys[256]; //키보드 입력
	char _keyL = 'a', _keyR = 'd';

	//float CONTROLBLOCKSPEED = 1.875;
	float CONTROLBLOCKSPEED = 2.5;
	int32 SCREENWIDTH;
	int32 SCREENHEIGHT;

	const int32 baseWidth = 640;
	const int32 baseHeight = 1080;



	int _remainPlayer = 99;
	UIState* _state;

	ClientServiceRef _service;

	bool _exit = false;

	int32 _roomNumber = -1;
	wstring _ip;
	int _port;
	string _key;

	unordered_map<string, int> index;
};

extern ClientPtr GM;

