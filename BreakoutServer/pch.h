#pragma once

#define WIN32_LEAN_AND_MEAN // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#ifdef _DEBUG
#pragma comment(lib, "Debug\\ServerCore.lib")
#else
#pragma comment(lib, "Release\\ServerCore.lib")
#endif
#pragma comment(lib, "ws2_32.lib")


#include "CorePch.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "random"
#include "string.h"
#include "WinSock2.h"
#include <WS2tcpip.h>

