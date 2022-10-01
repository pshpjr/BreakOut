#pragma once

#define WIN32_LEAN_AND_MEAN // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#ifdef _DEBUG
#pragma comment(lib, "Debug\\libprotobufd.lib")
#pragma comment(lib, "Debug\\ServerCore.lib")
#else
#pragma comment(lib, "Release\\libprotobufd.lib")
#pragma comment(lib, "Release\\ServerCore.lib")
#endif

#include "CorePch.h"
#include "GameSession.h"

using GameSessionRef = shared_ptr<GameSession>;
