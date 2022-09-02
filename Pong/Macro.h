#pragma once
#include "pch.h"
using pt = glm::vec2;

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;