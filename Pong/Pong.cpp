#include "pch.h"
#include "Pong.h"

#include <string>


Pong::~Pong()
{
	Clear();
}

void Pong::Init()
{
	//변수 초기화 및 임의의 공 방향 정하기
	_state = GAME_LOAD;
	_life = 3;
	//std::random_device rd;
	//std::mt19937 gen(rd());
	//std::uniform_int_distribution<int> dis(1, 100);
	//_b->setVector({ dis(gen) / static_cast<double>(100),dis(gen) / static_cast<double>(100) });
	_control_block = new ControlBlock(MAPSIZE);
	_b = new Ball({ -2,0 }, { 1,1 }, 1,3);
	_b->setVector(glm::normalize(glm::vec2(0.35, 0.97 )));

	memset(Keys, 0, sizeof(Keys));
	//게임판 생성

	_update_requires.push_back(_control_block);
	_update_requires.push_back(_b);

	
	_blocks.push_back(new Block(pt(-MAPSIZE, -MAPSIZE + 10), pt(WALLTHICKNESS, MAPSIZE * 2), true)); //left
	_blocks.push_back(new Block(pt(MAPSIZE, -MAPSIZE + 10), pt(WALLTHICKNESS, MAPSIZE * 2), true));//right
	_blocks.push_back(new Block(pt(-MAPSIZE, MAPSIZE + 10), pt(MAPSIZE * 2 + WALLTHICKNESS, WALLTHICKNESS), true));//top


	_deadline = new Block(pt(-MAPSIZE, -MAPSIZE + 30), pt(MAPSIZE * 2, 3), true);//bottom

	//TODO: 두 개 하나로 통합
	for (int i = 0; i <4; i++) {
		for (int j = 0; j < MAPX; j ++) {
			_map[i][j] = 3;
		}
	}

	for (int i = -MAPSIZE + 20; i <= MAPSIZE - 20; i += BLOCKWIDTH) {
		for (int j = 20; j <= MAPSIZE - 20; j += BLOCKHEIGHT) {
			_blocks.push_back(new Block(pt(i, j), pt(BLOCKWIDTH, BLOCKHEIGHT)));
		}
	}

	_state = GAME_ACTIVE;
}

bool Pong::isDead() const
{
	return _life <= 0;
}

void Pong::Update()
{
	for (const auto i : _update_requires) {
		i->update();
	}

	block_collision_test();

	control_block_collision_test();

	ball_out_test();


}

void Pong::block_collision_test() const
{
	Collision collision(false, UP, { 0,0 });

	for (auto& i : _blocks) {
		if (i->isVisible() == false)
			continue;

		collision = CheckCollision(*_b, *i);
		if (collision.isCollision() == false)
			continue;

		//아래 코드들은 충돌한 경우 실행
		if (!i->_isSolid)
			i->swapVisibility();

		Direction dir = collision.collisionDirection();
		glm::vec2 diff_vector = collision.diffVector();
		if (dir == LEFT || dir == RIGHT)
		{
			_b->setXVectorInverse();

			float penetration = _b->getRadius() - std::abs(diff_vector.x);
			if (dir == LEFT)
				_b->move(penetration, 0);
			else
				_b->move(-penetration, 0);
		}
		else
		{
			_b->setYVectorInverse();

			float penetration = _b->getRadius() - std::abs(diff_vector.y);
			if (dir == UP)
				_b->move(0, -penetration);
			else
				_b->move(0, penetration);
			
		}
		break;
	}
}

void Pong::control_block_collision_test() const
{

	Collision collision = CheckCollision(*_b, *_control_block);
	if (collision.isCollision() == true)
	{
		float centerBoard = _control_block->getStart().x + _control_block->getSize().x / 2.0f;
		float distance = _b->getLocation().x + -centerBoard;
		float percentage = distance / (_control_block->getSize().x / 2.0f);

		glm::vec2 oldVelocity = _b->getVector();

		pt newVec = { percentage * 1 ,abs(oldVelocity.y) };

		_b->setVector(glm::normalize(newVec) * glm::length(oldVelocity));
	}

}

void Pong::ball_out_test() 
{
	Collision collision = CheckCollision(*_b, *_deadline);

	if (collision.isCollision() == false)
		return;

	
	_b->setYVectorInverse();
	_life--;

	if (isDead())
	{
		_state = GAME_END;
		Reset();
		_state = GAME_ACTIVE;
	}
	

}

void Pong::Render()
{
	glViewport(_viewportX, _viewportY, _width, _height);

	glClearColor(1, 1, 1, 1);

	glColor3f(1.0f, 0.0f, 1.0f);

	_b->draw();
	_control_block->draw();

	for (const auto& i : _blocks) {
		i->draw();
	}

	if(_isMyPlay)
		DrawText("Life: " + std::to_string(_life), 0, WINDOWSIZE * 0.8);

}

void Pong::Tick()
{
	ProcessInput(16.6);
	if (_state == GAME_ACTIVE) {
		Update();
		Render();
		
	}

}

void Pong::Reset()
{
	Clear();
	Init();
}

void Pong::DrawText(string str, float width, float height,float R, float G, float B)
{
	glColor3f(R, G, B);
	glRasterPos2f(width, height);
	for (char c : str) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}
}

Direction Pong::VectorDirection(glm::vec2 target) const
{
	glm::vec2 compass[] = {
	glm::vec2(0.0f, 1.0f),	// up
	glm::vec2(1.0f, 0.0f),	// right
	glm::vec2(0.0f, -1.0f),	// down
	glm::vec2(-1.0f, 0.0f)	// left
	};

	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}

Collision Pong::CheckCollision(const Ball& one, const Block& two) const
{
	// get center point circle first 
	glm::vec2 center = one.getLocation();
	// calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(two.getSize().x / 2.0f, two.getSize().y / 2.0f);
	glm::vec2 aabb_center(
		two.getStart().x + aabb_half_extents.x,
		two.getStart().y + aabb_half_extents.y
	);
	// get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// add clamped value to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// retrieve vector between center circle and closest point AABB and check if length <= radius
	difference = closest - center;
	float len = glm::length(difference);
	if ( len <= one.getRadius())
		return Collision(true, VectorDirection(difference), difference);
	else
		return Collision(false, UP, glm::vec2(0.0f, 0.0f));
}


void Pong::changeState(game_state state)
{
	_state = state;
}

void Pong::ProcessInput(float dt)
{
	float velocity = 1 * dt;
	// move playerboard
	if (this->Keys[_keyR])
	{
		_control_block->setVector({1,0});
		_control_block->setSpeed(1);
	}
	if (this->Keys[_keyL])
	{
		_control_block->setVector({ -1,0 });
		_control_block->setSpeed(1);
	}
}


void Pong::Clear()
{
	for (auto& i : _update_requires) {
		delete i;
	}
	_update_requires.clear();
	for (auto& i : _blocks) {
		delete i;
	}
	_blocks.clear();
	delete _deadline;
}
