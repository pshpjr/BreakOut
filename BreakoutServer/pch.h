#pragma once

#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

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

