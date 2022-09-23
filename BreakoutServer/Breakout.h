#pragma once
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


	Breakout(int32 width, int32 height, int32 x, int32 y) :
		_state(ALIVE), _width(width), _height(height), _viewportX(x), _viewportY(y),
		MAPLEFT(x + width * 0.1f), MAPRIGHT(x + width - width * 0.1f), MAPBOTTOM(y + height * 0.2), MAPTOP(y + height - height * 0.24f)
	{
		int mapWidth = MAPRIGHT - MAPLEFT;
		_mapwidth = mapWidth;
		float blockGap = mapWidth * 0.1f;
		BLOCKWIDTH = (mapWidth - blockGap * 2.0f) / 10;
		BLOCKHEIGHT = BLOCKWIDTH / 2;
		Init();
	}
	Breakout(int32 width, int32 height, int32 x, int32 y, char keyL, char keyR) : Breakout(width, height, x, y)
	{
		_keyL = keyL;
		_keyR = keyR;
	}

	~Breakout();

	void Init();
	void Update();//����
	void Render();
	void Tick();
	void Reset();

	void Clear();


	void changeState(PlayerState state);
	bool isDead() const;

private:
	Direction VectorDirection(glm::vec2 target) const;
	Collision CheckCollision(const Ball& one, const Block& two) const;

	void block_collision_test() const;
	void ball_out_test();
	void control_block_collision_test() const;
	void control_block_out_test_and_modify() const;

public:
	Ball* _b;// �÷��̾��� ��
	ControlBlock* _control_block; // �� Ƣ��� ����

	std::vector<Block*> _blocks; //������ �� �ܺ� ��
	Block* _deadline; //���� ����°� �����ϱ� ���� ��
	std::vector<Moveable*> _update_requires; // ��ġ�� ���ϴ� �ֵ��� �� ���� �����ϱ� ����

	Block* _deadBlind;



	bool _isMyPlay = false;

	bool noGUI = false;
private:
	PlayerState _state;
	int32 _width;
	int32 _height;
	int32 _viewportX = 0, _viewportY = 0;

	const float MAPLEFT, MAPRIGHT, MAPBOTTOM, MAPTOP;
	float BALLSIZE = 10;

	int WALLTHICKNESS = 15;
	int BLOCKWIDTH = 100;
	int BLOCKHEIGHT = 50;
	float BALLSPEED = 4;

	float _deltaTime = 16.6;//60fps


	const int MAPROW = 10;
	const int MAPCOL = 5;

	int _map[10][5];

	int _life = 3;
	int _mapwidth;

	//TEMP
	char _keyL = 'a', _keyR = 'd';
};



