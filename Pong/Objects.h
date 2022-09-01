#pragma once
#include "Pt.h"


class StaticObject {
public:
	StaticObject() = default;
	virtual void draw() const {}

public:
	void swapVisibility() {
		this->_visible = !this->_visible;
	}
	bool isVisible() const {
		return this->_visible;
	}
private:
	bool _visible = true;
};

class Moveable {

public:
	Moveable() = default;
	Moveable(const pt location, const pt vector, const double speed) : _location(location), _vector(vector), _speed(speed) {}

	void setVector(const pt vector) { _vector = vector; }
	void setSpeed(const double speed) { _speed = speed; }
	void setXVectorInverse() { _vector.x *= -1; }
	void setYVectorInverse() { _vector.y *= -1; }
	void setVectorInverse() { _vector.x *= -1; _vector.y *= -1; }
	pt getVector() const { return _vector; }
	pt getLocation() const { return _location; }
	virtual void update() {
		_location += _vector * _speed;
	}
protected:
	pt _location{};
	pt _vector{};
	double _speed{};
};

class Block : public StaticObject {
public:
	Block() = default;
	Block(const pt p1, const pt p2) : _start(p1), _size(p2), _life(3) {}
	Block(const pt p1, const pt p2, const int life) : _start(p1), _size(p2), _life(life) {}

	void decreaseLife() { _life -= 1; }
	int getLife() const { return _life; }
	bool isDead() const { return _life <= 0; }
	pt getStart() const { return _start; }
	pt getSize() const { return _size; }

	void draw() const override
	{
		if (!isVisible())
			return;

		glColor3f(0, 0, 0);

		switch (getLife()) {
		case 5:
			glColor3f(0, 0, 255);
			break;
		case 4:
			glColor3f(0, 255, 0);
			break;
		case 3:
			glColor3f(255, 255, 0);
			break;
		case 2:
			glColor3f(0, 255, 255);
			break;
		case 1:
			glColor3f(255, 0, 0);
			break;
		default:
			break;
		}

		glBegin(GL_POLYGON);
		glVertex2d(_start.x, _start.y);
		glVertex2d(_start.x + _size.x, _start.y);
		glVertex2d(_start.x + _size.x, _start.y + _size.y);
		glVertex2d(_start.x, _start.y + _size.y);
		glEnd();

	}

protected:
	pt _start{};
	pt _size{};
private:
	int _life{};
};

class Wall : public Block {
public:
	Wall(const pt p1, const pt p2) : Block(p1, p2, 99999999) {}
};

class Ball : public StaticObject, public Moveable {
public:
	Ball() = default;
	Ball(const pt location, const pt vector, const double speed, const double ballSize) : Moveable(location, vector, speed),_ballsize(ballSize) {}

	double size = _ballsize;

	bool isPointInBall(const pt& point) const {
		const double dist = _location.distSquare(point);
		const double b_square = _ballsize * _ballsize;
		return  dist <= b_square;
	}

	void draw() const override
	{
		glColor3f(1.0f, 0.0f, 1.0f);

		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++) {
			const double angle = i * 3.141592 / 180;
			const double x = _location.x + _ballsize * cos(angle);
			const double y = _location.y + _ballsize * sin(angle);
			glVertex2d(x, y);
		}
		glEnd();
	}

private:
	double _ballsize = 1;
};

class ControlBlock : public Block, public Moveable { //컨트롤 박스는 로케이션이 좌하단.
public:
	ControlBlock(int32 mapSize) : Block({ -20, -40 }, { 40, 2 }), Moveable({ 0, 0 }, { 0, 0 }, 0), _mapSize(mapSize) {}

	void update() override
	{
		_start += _vector * _speed;
		if (_start.x < -_mapSize)
			_start.x = -_mapSize;
		if (_start.x + _size.x > _mapSize)
			_start.x = _mapSize - _size.x;

		if (_speed <= 0.1)
			_speed = 0;
		else
			_speed *= 0.85;
	}

	pt calcBallReflectVector(const Ball* ball) const
	{
		const double center = _start.x + (_size.x / 2);
		const double delta = -(center - ball->getLocation().x) / (_size.x / 2);
		double result = ball->getVector().x > 0 ? delta : -delta;

		return { result,ball->getVector().y };
	}
private:
	int32 _mapSize = 0;
};