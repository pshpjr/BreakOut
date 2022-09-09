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
		GAME_END
	};

private:
	Pong() { Init(); }

public:

	Pong(int32 width, int32 height) :Pong()
	{
		_state = GAME_LOAD;
		_width = width; 
		_height = height;
	}

	//나중에 삭제
	Pong(int32 width, int32 height,int32 windowSize): Pong(width, height)
	{
		WINDOWSIZE = windowSize;
	}

	Pong(int32 width, int32 height, int32 windowSize, float delta): Pong(width, height, windowSize)
	{
		_deltaTime = delta;
	}

	~Pong();

	void Init();
	void Update();
	void Render();
	void Tick();
	void Reset();
	void ProcessInput(float dt);
	void Clear();


	void DrawText(string str, float width, float height);



	void changeState(game_state state);
	bool isDead() const;

private:
	Direction VectorDirection(glm::vec2 target) const;
	Collision CheckCollision(const Ball& one, const Block& two) const;

	void block_collision_test() const;
	void ball_out_test();
	void control_block_collision_test() const;


public:
	Ball* _b;
	ControlBlock* _control_block;

	std::vector<Block*> _blocks;
	Block* _deadline; 
	std::vector<Moveable*> _update_requires;

	int Keys[1024];


private:
	game_state _state;
	int32 _width;
	int32 _height;

	int WINDOWSIZE = 100;
	int MAPSIZE = WINDOWSIZE - 20;
	float BALLSIZE = 2.5;

	float _deltaTime = 16.6;//60fps
	

	int _map[10][10];

	int _life = 3;
};

