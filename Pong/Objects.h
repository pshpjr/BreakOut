#pragma once
#include "pch.h"

#include "Macro.h"


class StaticObject {
public:
	StaticObject() = default;
	virtual ~StaticObject() = default;
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
	virtual ~Moveable() = default;
	Moveable(const pt location, const pt vector, const float speed) : _location(location), _vector(vector), _speed(speed) {}

	void setVector(const pt vector) { _vector = vector; }
	void setSpeed(const float speed) { _speed = speed; }
	void setXVectorInverse() { _vector.x *= -1; }
	void setYVectorInverse() { _vector.y *= -1; }
	void setVectorInverse() { _vector.x *= -1; _vector.y *= -1; }
	pt getVector() const { return _vector; }
	pt getLocation() const { return _location; }
	void setRatio(float r) { _ratio = r; }
	virtual void update() {
		_location += _vector * _speed;
	}

protected:
	pt _location{};
	pt _vector{};
	float _speed{};
	float _ratio = 1;
};


class Block : public StaticObject {
public:
	Block() :_life(3){};
	Block(const pt p1, const pt p2) : _start(p1), _size(p2), _life(3) {}
	Block(const pt p1, const pt p2, const int life) : _start(p1), _size(p2), _life(life) {}
	Block(const pt p1, const pt p2, bool solid) : _isSolid(solid), _start(p1), _size(p2) {}
	void decreaseLife() { _life -= 1; }
	int getLife() const { return _life; }
	bool isDead() const { return _life <= 0; }
	pt getStart() const { return _start; }
	pt getSize() const { return _size; }
	void setStart(const pt& start) { _start = start; }
	void setSize(const pt& size) { _size = size; }

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
		glVertex2f(_start.x, _start.y);
		glVertex2f(_start.x + _size.x, _start.y);
		glVertex2f(_start.x + _size.x, _start.y + _size.y);
		glVertex2f(_start.x, _start.y + _size.y);
		glEnd();

		glColor3f(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(_start.x, _start.y);
		glVertex2f(_start.x + _size.x, _start.y);
		glVertex2f(_start.x + _size.x, _start.y + _size.y);
		glVertex2f(_start.x, _start.y + _size.y);
		glEnd();

	}

	void draw(float R, float G, float B) const
	{
		if (!isVisible())
			return;

		glColor3f(R, G, B);

		glBegin(GL_POLYGON);
		glVertex2f(_start.x, _start.y);
		glVertex2f(_start.x + _size.x, _start.y);
		glVertex2f(_start.x + _size.x, _start.y + _size.y);
		glVertex2f(_start.x, _start.y + _size.y);
		glEnd();

		glColor3f(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(_start.x, _start.y);
		glVertex2f(_start.x + _size.x, _start.y);
		glVertex2f(_start.x + _size.x, _start.y + _size.y);
		glVertex2f(_start.x, _start.y + _size.y);
		glEnd();

	}

public:
	bool _isSolid = false;

protected:
	pt _start{};
	pt _size{};
private:
	int _life{};
};


class Ball : public StaticObject, public Moveable {
public:
	Ball() = default;
	Ball(const pt location, const pt vector, const float speed, const float ballSize) :
		Moveable(location, vector, speed), _radius(ballSize) {}

	bool isPointInBall(const pt& point) const {
		return  distance(_location, point) <= _radius;
	}

	float getRadius() const
	{
		return _radius;
	}

	void move(float dx, float dy)
	{
		_location.x += dx;
		_location.y += dy;
	}

	void draw() const override
	{
		glColor3f(1.0f, 0.0f, 1.0f);

		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++) {
			const float angle = (float)i * 3.14f / 180;
			const float x = _location.x + _radius * cos(angle);
			const float y = _location.y + _radius * sin(angle);
			glVertex2f(x, y);
		}
		glEnd();
	}

private:
	float _radius = 2;
};

//TODO: mapsize 변수 외부로 빼기
//클래스 좀 이상함
class ControlBlock : public Block, public Moveable { //컨트롤 박스는 로케이션이 좌하단. 위치는 start 사용
public:
	ControlBlock() :Block({},{},true), Moveable({0, 0}, {0, 0}, 0) {}
	
	void update() override
	{
		_start += _vector * _speed * _ratio;

		if (_speed <= 0.1f)
			_speed = 0;
		else
			_speed *= 0.85f;
	}

private:
};