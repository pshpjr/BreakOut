#pragma once

class UIState;
class Client
{
public:

	Client(int32 SCREENWIDHT, int32 SCREENHEIGHT,wstring ip, int port);
	void AddPong(int32 width, int32 height, int32 x, int32 y);


	bool Tick();


	bool Init();
	void Start();
	void End();

	void noGUI(bool value);
	void AddPong(int32 width, int32 height, int32 x, int32 y, char L, char R);

	bool ProcessInput(float dt);
	void ChangeState(UIState* state) { _state = state; }

	//���Ϳ� ���� ���� -> ���� Ȯ�� -> �̵�/���� �ؾ� �� -> �Ҹ��� ȣ��
	vector<BreakoutPtr> _pongs;
	BreakoutPtr _mainPlay;
	bool _noGUI = false;
	bool Keys[256]; //Ű���� �Է�
	char _keyL = 'a', _keyR = 'd';

	int CONTROLBLOCKSPEED = 8;

	int32 SCREENWIDTH;
	int32 SCREENHEIGHT;

	const int32 baseWidth = 640;
	const int32 baseHeight = 1080;

	//���� ������
	char recvBuf[1000];

	int _remainPlayer = 99;
	UIState* _state;

	ClientServiceRef _service;

	bool _exit = false;

	wstring _ip;
	int _port;
};

extern ClientPtr GM;

