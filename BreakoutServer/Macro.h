#pragma once
#include "pch.h"

class ServerSession;
class Player;
class Breakout;
class Client;


enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};
using pt = glm::vec2;
using PlayerRef = shared_ptr<Player>;
using ServerSessionRef = shared_ptr<ServerSession>;


template <typename T>
void wrap(T& OUT data, T low, T high)
{
	ASSERT_CRASH(low < high);
	const T n = (data - low) % (high - low);
	data = (n >= 0) ? (n + low) : (n + high);
}

#define USE_PROFILER

#ifdef USE_PROFILER

#define P_START OPTICK_FRAME("MainThread");
#define P_THREAD(NAME) OPTICK_THREAD(##NAME);
#define P_Event(NAME) OPTICK_EVENT(##NAME);
#define P_TEST_START int32 tick = GetTickCount();
#define P_TEST_END(time,string) if (GetTickCount() - tick > (time)) cout << (string) << endl;

#else
#define P_START 
#define P_THREAD(NAME) 
#define P_Event(NAME)
#define P_TEST_START 
#define P_TEST_END
#endif