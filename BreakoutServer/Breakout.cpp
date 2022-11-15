#include "pch.h"
#include "Breakout.h"
#include "Objects.h"
#include <string>



Breakout::~Breakout()
{
	Clear();
}

void Breakout::Init()
{
	//변수 초기화 및 임의의 공 방향 정하기
	_state = ALIVE;
	_life = 3;

	//객체에 들어가는 변수들 초기화
	float mapHeight = MAPTOP - MAPBOTTOM;
	pt controlSize = { CONTROLBLOCKWIDTH,3 };
	pt controlStart = { baseWidth / 2 - controlSize.x / 2, MAPBOTTOM + baseHeight * 0.1 };
	pt ballLocation = { _mapwidth / 2 + MAPLEFT,mapHeight * 0.3 + MAPBOTTOM };

	_control_block = new ControlBlock();
	_control_block->setStart(controlStart);
	_control_block->setSize(controlSize);


	_b = new Ball(ballLocation, { 1,1 }, BALLSPEED, BALLSIZE);

	glm::vec2 beginVector(1, 1);

	_b->setVector(glm::normalize(beginVector));


	//게임판 생성
	_update_requires.push_back(_control_block);
	_update_requires.push_back(_b);

	_deadBlind = new Block({ 0,0 }, { baseWidth,baseHeight });

	_blocks.push_back(new Block(pt(MAPLEFT - WALLTHICKNESS, MAPBOTTOM), pt(WALLTHICKNESS, mapHeight), true)); //left
	_blocks.push_back(new Block(pt(MAPRIGHT, MAPBOTTOM), pt(WALLTHICKNESS, mapHeight), true));//right
	_blocks.push_back(new Block(pt(MAPLEFT - WALLTHICKNESS, MAPTOP), pt(_mapwidth + WALLTHICKNESS * 2, WALLTHICKNESS), true));//top

	_deadline = new Block(pt(MAPLEFT, MAPBOTTOM), pt(_mapwidth, WALLTHICKNESS), true);//bottom

	//TODO: 두 개 하나로 통합
	for (int i = 0; i < MAPROW; i++) {
		for (int j = 0; j < MAPCOL; j++) {
			_map[i][j] = 3;
		}
	}
	int start = MAPLEFT + BLOCKGAP;

	int startH = MAPBOTTOM + mapHeight * 0.6f;

	for (int i = 0; i < MAPROW; i++) {
		for (int j = 0; j < MAPCOL; j++) {
			_blocks.push_back(new Block(pt(start + i * BLOCKWIDTH, startH + j * BLOCKHEIGHT), pt(BLOCKWIDTH, BLOCKHEIGHT)));
		}
	}

}

bool Breakout::isDead() const
{
	return _state == DEAD;
}

void Breakout::Update()
{
	if (isDead())
		return;

	for (const auto i : _update_requires) {
		i->update();
	}
	block_collision_test();

	control_block_collision_test();

	ball_out_test();

	control_block_out_test_and_modify();

}

void Breakout::block_collision_test() const
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

void Breakout::control_block_collision_test() const
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

void Breakout::control_block_out_test_and_modify() const
{
	pt cbLocation = _control_block->getStart();
	pt cbSize = _control_block->getSize();
	if (cbLocation.x < MAPLEFT)
		_control_block->setStart({ MAPLEFT,cbLocation.y });
	if (cbLocation.x + cbSize.x > MAPRIGHT)
		_control_block->setStart({ MAPRIGHT - _control_block->getSize().x,cbLocation.y });

}

void Breakout::ball_out_test()
{
	Collision collision = CheckCollision(*_b, *_deadline);

	if (collision.isCollision() == false)
		return;
	glm::vec2 oldVelocity = _b->getVector();

	_b->setVector({ oldVelocity.x, abs(oldVelocity.y) });
	_life--;

	//if (isDead())
	//{
	//	_state = WIN;
	//	Reset();
	//	_state = PLAYING;
	//}

	if (_life <= 0)
		_state = DEAD;
}

void Breakout::Render()
{

	for (const auto& i : _blocks) {
		i->draw();
	}
}

void Breakout::Tick()
{
	if (_state == ALIVE)
		Update();

	if (noGUI)
		return;
	Render();
}

void Breakout::Reset()
{
	Clear();
	Init();
}



Direction Breakout::VectorDirection(glm::vec2 target) const
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

Collision Breakout::CheckCollision(const Ball& one, const Block& two) const
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
	if (len <= one.getRadius())
		return Collision(true, VectorDirection(difference), difference);
	else
		return Collision(false, UP, glm::vec2(0.0f, 0.0f));
}


void Breakout::changeState(PlayerState state)
{
	_state = state;
}



void Breakout::Clear()
{

	ASSERT_CRASH(_blocks.size() != 0)
	ASSERT_CRASH(_update_requires.size() != 0)
	ASSERT_CRASH(_deadline != nullptr)

	for (auto i : _update_requires) {
		delete i;
		i = nullptr;
	}
	_update_requires.clear();
	for (auto& i : _blocks) {
		delete i;
		i = nullptr;
	}
	_blocks.clear();
	SAFE_DELETE( _deadline);
}
