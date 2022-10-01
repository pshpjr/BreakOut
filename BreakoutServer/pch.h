#pragma once

#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#ifdef _DEBUG
#pragma comment(lib, "Debug\\ServerCore.lib")
#pragma comment(lib, "Debug\\libprotobufd.lib")
#else
#pragma comment(lib, "Release\\ServerCore.lib")
#endif
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include "CorePch.h"
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>

#include "ServerSession.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "SocketUtils.h"
#include "Memory.h"

using GameSessionRef = shared_ptr<ServerSession>;