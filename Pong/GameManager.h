#pragma once

class UIState;
class GameManager
{
public:

	GameManager(int32 SCREENWIDHT, int32 SCREENHEIGHT);
	void AddPong(int32 width, int32 height, int32 x, int32 y);

	void Tick();
	void AddPong(int32 width, int32 height, int32 x, int32 y, char L, char R);
	void Start();
	void noGUI(bool value);
	bool Init();
	void ProcessInput(float dt);
	void ChangeState(UIState* state) { _state = state; }

	//���Ϳ� ���� ���� -> ���� Ȯ�� -> �̵�/���� �ؾ� �� -> �Ҹ��� ȣ��
	vector<PongPtr> _pongs;
	PongPtr _mainPlay;
	bool _noGUI = false;
	bool Keys[256]; //Ű���� �Է�
	char _keyL = 'a', _keyR = 'd';
	int32 _width = 0, _height = 0; 
	int CONTROLBLOCKSPEED = 8;

	//���� ������
	char recvBuf[1000];

	UIState* _state;
};


