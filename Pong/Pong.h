#pragma once
#include "Objects.h"

class Collision
{
public:
	Collision(bool result, Direction vectorDirection, glm::vec2 resultVec) : _cResult(result),_d(vectorDirection),_diffVec(resultVec){
	}

	bool isCollision() const
	{
		return _cResult;
	}

	Direction collisionDirection() const
	{
		return _d;
	}

	glm::vec2 diffVector() const
	{
		return _diffVec;
	}

private:
	bool _cResult;
	Direction _d;
	glm::vec2 _diffVec;
	
};

class Pong
{
public:
	enum game_state
	{
		GAME_ACTIVE,
		GAME_LOAD,
		GAME_MENU,
		GAME_END,
		GAME_DEAD
	};

private:

public:


	Pong(int32 width, int32 height, int32 x, int32 y) :
		_state(GAME_LOAD), _width(width), _height(height), _viewportX(x), _viewportY(y),
		MAPLEFT(x + width * 0.1f), MAPRIGHT(x + width - width * 0.1f), MAPBOTTOM(y + height * 0.2), MAPTOP(y + height - height * 0.24f)
	{
		int mapWidth = MAPRIGHT - MAPLEFT;
		_mapwidth = mapWidth;
		float blockGap = mapWidth * 0.1f;
		BLOCKWIDTH = (mapWidth - blockGap * 2.0f) / 10;
		BLOCKHEIGHT = BLOCKWIDTH / 2;
		Init();
	}
	Pong(int32 width, int32 height, int32 x, int32 y, char keyL, char keyR) : Pong(width, height,x,y)
	{
		_keyL = keyL;
		_keyR = keyR;
	}

	~Pong();

	void Init();
	void Update();//서버
	void Render();
	void Tick();// 필요x
	void Reset();//서버. 모든 클라 접속 끊은 후 호출
	void ProcessInput(float dt);
	void Clear();


	void drawText(string str, float width, float height, float R = 0, float G = 0, float B = 0);



	void changeState(game_state state);
	bool isDead() const;

private:
	Direction VectorDirection(glm::vec2 target) const;
	Collision CheckCollision(const Ball& one, const Block& two) const;

	void block_collision_test() const;
	void ball_out_test();
	void control_block_collision_test() const;
	void control_block_out_test_and_modify() const;

public:
	Ball* _b;// 플레이어의 공
	ControlBlock* _control_block; // 공 튀기는 막대

	std::vector<Block*> _blocks; //벽돌과 맵 외부 벽
	Block* _deadline; //공이 벗어나는걸 판정하기 위한 선
	std::vector<Moveable*> _update_requires; // 위치가 변하는 애들을 한 번에 갱신하기 위해

	Block* _deadBlind;

	bool Keys[256]; //키보드 입력

	bool _isMyPlay = false;

	bool noGUI = false;
private:
	game_state _state;
	int32 _width;
	int32 _height;
	int32 _viewportX = 0, _viewportY = 0;

	const float MAPLEFT, MAPRIGHT,MAPBOTTOM,MAPTOP;
	float BALLSIZE = 10;

	int WALLTHICKNESS = 15;
	int BLOCKWIDTH = 100;
	int BLOCKHEIGHT = 50;
	float BALLSPEED = 4;
	int CONTROLBLOCKSPEED = 8;
	float _deltaTime = 16.6;//60fps


	const int MAPROW = 10;
	const int MAPCOL = 5;

	int _map[10][5];

	int _life = 3;
	int _mapwidth;
	char _keyL = 'a', _keyR = 'd';

};

