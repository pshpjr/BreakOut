#pragma once
class GameManager
{
public:

	GameManager();
	void AddPong(int32 width, int32 height, int32 x, int32 y, int32 windowSize);

	void Tick();
	void AddPong(int32 width, int32 height, int32 x, int32 y, int32 windowSize, char L, char R);


	//���Ϳ� ���� ���� -> ���� Ȯ�� -> �̵�/���� �ؾ� �� -> �Ҹ��� ȣ��
	vector<Pong> _pongs;

};

