#pragma once
#include "Objects.h"

class Pong
{

public:
	Pong(int32 width, int32 height)
		:_state(GAME_LOAD), _width(width), _height(height){  }

	Pong(int32 width, int32 height,int32 windowSize)
		:_state(GAME_LOAD), _width(width), _height(height),_WINDOWSIZE(windowSize) {  }
	Pong(int32 width, int32 height, int32 windowSize, double delta)
		:_state(GAME_LOAD), _width(width), _height(height), _WINDOWSIZE(windowSize),_deltaTime(delta) {  }

	~Pong();

	void Init();
	void Update();
	void Render();
	void tick();
	void Reset();
	void DrawText(string str, float width, float height);

	Direction VectorDirection(glm::vec2 target) const;
	Collision CheckCollision(const Ball& one, const Block& two) const;
	void ProcessInput(float dt);
	void Clear();

public:
	Ball* _b;
	ControlBlock* _control_block;

	std::vector<Block*> _blocks;
	Block* _deadline; 
	std::vector<Moveable*> _update_requires;

	int Keys[1024];

private:
	enum game_state
	{
		GAME_ACTIVE,
		GAME_LOAD,
		GAME_MENU,
		GAME_END
	};
	const glm::vec2 INITIAL_BALL_VELOCITY = { 100.0f, -350.0f };
private:
	game_state _state;
	int32 _width;
	int32 _height;

	int _WINDOWSIZE = 100;
	int _MAPSIZE = _WINDOWSIZE - 20;

	double _deltaTime = 16.66;//60fps

	const unsigned char XCOLLSION = 1 << 0;
	const unsigned char YCOLLSION = 1 << 1;

	int _Map[10][10];

	int _life = 3;
};

