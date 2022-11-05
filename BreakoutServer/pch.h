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


#include "CorePch.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "ThreadManager.h"
#include "Memory.h"
#include "Macro.h"
#include "Protocol.pb.h"
#include "Player.h"

#include <iostream>

#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>


#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>

#include "ServerSession.h"

#include "SocketUtils.h"




