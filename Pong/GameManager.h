#pragma once
class GameManager
{
public:

	GameManager();
	void AddPong(int32 width, int32 height, int32 x, int32 y);

	void Tick();
	void AddPong(int32 width, int32 height, int32 x, int32 y, char L, char R);


	//벡터에 값을 넣음 -> 벡터 확장 -> 이동/복사 해야 함 -> 소멸자 호출
	vector<Pong> _pongs;

};

