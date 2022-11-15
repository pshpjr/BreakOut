#pragma once
#include "Macro.h"

class Moveable;
class ControlBlock;
class Ball;
class Block;

class Collision
{
public:
	Collision(bool result, Direction vectorDirection, glm::vec2 resultVec) : _cResult(result), _d(vectorDirection), _diffVec(resultVec) {
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

class Breakout
{
public:
	enum PlayerState
	{
		DEAD,
		ALIVE,
		WIN
	};


	Breakout(int32 width = 640, int32 height = 1080, int32 x = 640, int32 y = 0) : MAPLEFT(baseWidth * 0.05f), MAPRIGHT(baseWidth * 0.95f),
		MAPBOTTOM(baseHeight * 0.2f), MAPTOP(baseHeight * 0.75f),
		_state(ALIVE), _width(width), _height(height), _viewportX(x), _viewportY(y)
	{
		_mapwidth = MAPRIGHT - MAPLEFT;
		Init();
	}
	Breakout(int32 width, int32 height, int32 x, int32 y, char keyL, char keyR) : Breakout(width, height, x, y)
	{
		_keyL = keyL;
		_keyR = keyR;
	}

	~Breakout();

	void Init();
	void Update();//서버
	void Render();
	void Tick();
	void Reset();

	void Clear();


	void changeState(PlayerState state);
	void SetDead() { _state = DEAD; }

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



	bool _isMyPlay = false;

	bool noGUI = false;
	int _life = 3;
private:
	PlayerState _state;

	//뷰포트 설정 
	int32 _width;
	int32 _height;
	int32 _viewportX = 0, _viewportY = 0;

	const int32 baseWidth = 640;
	const int32 baseHeight = 1080;

	const float MAPLEFT, MAPRIGHT, MAPBOTTOM, MAPTOP;

	const float BALLSIZE = 10;
	const int WALLTHICKNESS = 15;
	const int BLOCKWIDTH = 46;
	const int BLOCKHEIGHT = 23;
	const int BLOCKGAP = 57;

	const float BALLSPEED = 4;
	const int CONTROLBLOCKSPEED = 8;
	const int CONTROLBLOCKWIDTH = 200;


	float _deltaTime = 16.6;//60fps


	const int MAPROW = 10;
	const int MAPCOL = 5;

	int _map[10][5];


	int _mapwidth;

	//TEMP
	char _keyL = 'a', _keyR = 'd';
};

