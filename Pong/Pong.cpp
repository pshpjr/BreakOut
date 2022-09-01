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
	_b = new Ball({ -2,0 }, { 1,1 }, 1,1);
	_b->setVector({ 0.35,0.97 });

	_update_requires.push_back(_control_block);
	_update_requires.push_back(_b);

	//B->setVector({ dis(gen) / static_cast<double>(100),dis(gen) / static_cast<double>(100) });
	printf("%f%f", _b->getVector().x, _b->getVector().y);
	_blocks.push_back(new Wall(pt(-_MAPSIZE, -_MAPSIZE), pt(2, _MAPSIZE * 2)));
	_blocks.push_back(new Wall(pt(_MAPSIZE, -_MAPSIZE), pt(2, _MAPSIZE * 2)));
	_blocks.push_back(new Wall(pt(-_MAPSIZE, _MAPSIZE), pt(_MAPSIZE * 2 + 2, 2)));
	_blocks.push_back(new Wall(pt(-_MAPSIZE, -_MAPSIZE), pt(_MAPSIZE * 2, 2)));



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
		if (i->isVisible() == false)
			continue;

		collision_result = collision_test(i, _b);

		if (collision_result != 0) {
			i->decreaseLife();
			if (i->isDead())
				i->swapVisibility();
			if (inverse_vector_info == 0)
				inverse_vector_info = collision_result;
		}
	}
	collision_result = collision_test(_control_block, _b);

	if (collision_result != 0) {
		if (inverse_vector_info == 0)
			inverse_vector_info = collision_result;
		_b->setVector(_control_block->calcBallReflectVector(_b));
	}

	if (inverse_vector_info & XCOLLSION)
		_b->setXVectorInverse();

	if (inverse_vector_info & YCOLLSION) {
		_b->setYVectorInverse();
	}


	for (const auto i : _update_requires) {
		i->update();
	}
	//glutPostRedisplay();
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

	Update();

	glutPostRedisplay();
	glutSwapBuffers();
}

int Pong::collision_test(const Block* box, const Ball* ball) const
{
	
	int result = 0;
	const pt ball_location = ball->getLocation();
	const pt box_start = box->getStart();
	const pt box_size = box->getSize();
	pt closest_point = ball->getLocation();


	if (ball_location.x < box_start.x) {
		closest_point.x = box_start.x;
	}
	else if (ball_location.x > box_start.x + box_size.x) {
		closest_point.x = box_start.x + box_size.x;
	}
	if (ball_location.y < box_start.y) {
		closest_point.y = box_start.y;
	}
	else if (ball_location.y > box_start.y + box_size.y) {
		closest_point.y = box_start.y + box_size.y;
	}
	if (ball->isPointInBall(closest_point)) {
		const double delta_x = closest_point.x - ball_location.x;
		const double delta_y = closest_point.y - ball_location.y;



		if (delta_x != 0)
			result |= XCOLLSION;
		if (delta_y != 0 && !(result && XCOLLSION))
			result |= YCOLLSION;
		//if (deltax == 0 && deltay == 0) {
		//	중점이 사각형 내부인 경우 
		//}

	}

	return result;
	
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
