#pragma once
#include "pch.h"
#include "fstream"
class DummySession;
class ClientSession;
class Breakout;
class Client;



const int KEY_LENGTH = 5;

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

using BreakoutPtr = shared_ptr<Breakout>;
using ClientPtr = shared_ptr<Client>;
using ClientSessionRef = shared_ptr<ClientSession>;
using DummySessionRef = shared_ptr<DummySession>;

inline void drawText(string str, float width, float height, float R = 0, float G = 0, float B = 0)
{
	glColor3f(R, G, B);
	glRasterPos2f(width, height);
	for (char c : str) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}
}

template <typename T>
void wrap(T& OUT data, T low, T high)
{
	ASSERT_CRASH(low < high);
	const T n = (data - low) % (high - low);
	data = (n >= 0) ? (n + low) : (n + high);
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

inline bool isKeyStateChanged(char c, bool& state)
{
	bool isPressed = isKeyPressing(c);
	bool changed = isPressed != state;
	state = isPressed;
	return changed;
}

inline std::string random_string(std::string::size_type length)
{
	static auto& chrs = "0123456789"
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	thread_local static std::mt19937 rg{ std::random_device{}() };
	thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

	std::string s;

	s.reserve(length);

	while (length--)
		s += chrs[pick(rg)];

	return s;
}

inline string GetKey()
{
	string key;
	std::ifstream fin("key.txt");

	if (fin.fail())
	{
		std::ofstream fout("key.txt");
		key = random_string(KEY_LENGTH);

		fout << key;
		fout.close();

		return key;
	}

	fin >> key;

	fin.close();

	return key;
}
