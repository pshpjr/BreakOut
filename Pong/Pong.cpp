#include "pch.h"
#include "Pong.h"



Pong::~Pong()
{
	Clear();
}

void Pong::Init()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 100);

	_control_block = new ControlBlock(_MAPSIZE);
	_b = new Ball({ -2,0 }, { 1,1 }, 1,3);
	_b->setVector(glm::normalize(glm::vec2(0.35, 0.97 )));

	_update_requires.push_back(_control_block);
	_update_requires.push_back(_b);

	//B->setVector({ dis(gen) / static_cast<double>(100),dis(gen) / static_cast<double>(100) });
	printf("%f%f", _b->getVector().x, _b->getVector().y);
	_blocks.push_back(new Block(pt(-_MAPSIZE, -_MAPSIZE + 30), pt(3, _MAPSIZE * 2), true));
	_blocks.push_back(new Block(pt(_MAPSIZE, -_MAPSIZE + 30), pt(3, _MAPSIZE * 2), true));
	_blocks.push_back(new Block(pt(-_MAPSIZE, _MAPSIZE + 30), pt(_MAPSIZE * 2, 3), true));
	_blocks.push_back(new Block(pt(-_MAPSIZE, -_MAPSIZE + 30), pt(_MAPSIZE * 2, 3), true));

	for (int i = 0; i <4; i++) {
		for (int j = 0; j < MAPX; j ++) {
			_Map[i][j] = 3;
		}
	}


	for (int i = -_MAPSIZE + 40; i <= _MAPSIZE - 40; i += 10) {
		for (int j = 30; j <= _MAPSIZE - 30; j += 5) {
			_blocks.push_back(new Block(pt(i, j), pt(10, 5)));
		}
	}


}

void Pong::Update()
{
	int collision_result;
	int inverse_vector_info = 0;
	for (auto& i : _blocks) {
		if (i->isVisible())
		{
			Collision collision = CheckCollision(*_b, *i);
			if (std::get<0>(collision)) // if collision is true
			{
				// destroy block if not solid
				if (!i->_isSolid)
					i->swapVisibility();
				// collision resolution
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
				if (dir == LEFT || dir == RIGHT) // horizontal collision
				{
					_b->setXVectorInverse(); // reverse horizontal velocity
					// relocate
					float penetration = _b->getRadius() - std::abs(diff_vector.x);
					if (dir == LEFT)
						_b->move(penetration,0); // move ball to right
					else
						_b->move(-penetration, 0); // move ball to left;
				}
				else // vertical collision
				{
					_b->setYVectorInverse(); // reverse vertical velocity
					// relocate
					float penetration = _b->getRadius() - std::abs(diff_vector.y);
					if (dir == UP)
						_b->move(0, -penetration); // move ball back up
					else
						_b->move(0, penetration); // move ball back down
				}
			}
		}
	}


	Collision result = CheckCollision(*_b, *_control_block);
	if (std::get<0>(result))
	{

		float centerBoard = _control_block->getStart().x + _control_block->getSize().x / 2.0f;
		float distance = _b->getLocation().x + - centerBoard;
		float percentage = distance / (_control_block->getSize().x / 2.0f);

		glm::vec2 oldVelocity = _b->getVector();

		pt newVec = {   percentage * 1 ,abs(oldVelocity.y)};

		_b->setVector (glm::normalize(newVec) * glm::length(oldVelocity));

	}

	ProcessInput(1);


	for (const auto i : _update_requires) {
		i->update();
	}
	
	Render();
}

void Pong::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);

	glColor3f(1.0f, 0.0f, 1.0f);

	_b->draw();
	_control_block->draw();

	for (const auto& i : _blocks) {
		i->draw();
	}


	glutPostRedisplay();
	glutSwapBuffers();
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
		return std::make_tuple(true, VectorDirection(difference), difference);
	else
		return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}

void Pong::ProcessInput(float dt)
{
	float velocity = 1 * dt;
	// move playerboard
	if (this->Keys['d'])
	{
		_control_block->setVector({1,0});
		_control_block->setSpeed(2);
	}
	if (this->Keys['a'])
	{
		_control_block->setVector({ -1,0 });
		_control_block->setSpeed(2);
	}
}


void Pong::Clear()
{
	delete _b;
	for (const auto i : _update_requires) {
		delete i;
	}
	delete _control_block;
	for (auto& i : _blocks) {
		delete i;
	}
}
