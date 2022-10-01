#pragma once

#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#include "CorePch.h"
#include "Protocol.pb.h"

#ifdef _DEBUG
#pragma comment(lib, "Debug\\libprotobufd.lib")
#pragma comment(lib, "Debug\\ServerCore.lib")
#else
#pragma comment(lib, "Libraries\\Release\\libprotobuf.lib")
#pragma comment(lib, "Libraries\\Release\\ServerCore.lib")
#endif
