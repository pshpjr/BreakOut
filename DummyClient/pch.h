#pragma once

#define WIN32_LEAN_AND_MEAN // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#include "CorePch.h"
#include "Protocol.pb.h"

#ifdef _DEBUG
#pragma comment(lib, "Debug\\libprotobufd.lib")
#pragma comment(lib, "Debug\\ServerCore.lib")
#else
#pragma comment(lib, "Libraries\\Release\\libprotobuf.lib")
#pragma comment(lib, "Libraries\\Release\\ServerCore.lib")
#endif
