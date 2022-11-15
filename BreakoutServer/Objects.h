#pragma once
#include "pch.h"



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
	Block() :_life(3) {};
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
	}

	void draw(float R, float G, float B) const
	{
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

	}

private:
	float _radius = 2;
};

class ControlBlock : public Block, public Moveable { //컨트롤 박스는 로케이션이 좌하단. 위치는 start 사용
public:
	ControlBlock() :Block({}, {}, true), Moveable({ 0, 0 }, { 0, 0 }, 0) {}

	void update() override
	{
		_start += _vector * _speed * _ratio;
	}

private:
};