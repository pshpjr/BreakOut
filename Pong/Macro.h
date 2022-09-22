#pragma once

class Pong;
class GameManager;

enum GameState
{
	PLAYING,
	INIT,
	MATCHING,
	GAMEREADY,
	LOBBY,
	WIN,
	DEAD,
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};
using pt = glm::vec2;

using PongPtr = shared_ptr<Pong>;
using GMPtr = shared_ptr<GameManager>;



inline void drawText(string str, float width, float height, float R = 0, float G = 0, float B = 0)
{
	glColor3f(R, G, B);
	glRasterPos2f(width, height);
	for (char c : str) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}
}

template <typename T>
void clamp(T& OUT data,T low,T high)
{
	ASSERT_CRASH(low < high);
	const T n = (data - low) % (data - high);
	data = (data >= 0) ? (n + low) : (n + high);
}

inline bool isKeyPressing(char c)
{
#ifdef WIN32
	SHORT keyState = GetAsyncKeyState(toupper(c));
	if ((keyState & 0x8000))
		return true;
	return false;
#elif
#endif
}
