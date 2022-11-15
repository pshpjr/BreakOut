#pragma once

#define WIN32_LEAN_AND_MEAN // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#ifdef _DEBUG
#pragma comment(lib, "Debug\\ServerCore.lib")
#pragma comment(lib, "Debug\\libprotobufd.lib")
#pragma comment(lib, "Debug\\OptickCore.lib")
#else
#pragma comment(lib, "Release\\ServerCore.lib")
#pragma comment(lib, "Release\\libprotobuf.lib")
#pragma comment(lib, "Release\\OptickCore.lib")
#endif
#pragma comment(lib, "ws2_32.lib")


#include <atomic>
#include <mutex>
#include <iostream>
#include <windows.h>
#include <future>


#include "CorePch.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "Macro.h"
#include "Protocol.pb.h"
#include "ServerSession.h"

#include "SocketUtils.h"
#include "Memory.h"


#include "ThreadManager.h"

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>





using GameSessionRef = shared_ptr<ServerSession>;

