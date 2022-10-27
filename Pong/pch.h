#pragma once

#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#ifdef _DEBUG
#pragma comment(lib, "Debug\\ServerCore.lib")
#pragma comment(lib, "Debug\\libprotobufd.lib")
#pragma comment(lib, "Debug\\OptickCore.lib")
#else
#pragma comment(lib, "Release\\ServerCore.lib")
#pragma comment(lib, "Release\\libprotobuf.lib")
#pragma comment(lib, "Release\\OptickCore.lib")
#endif

#include "CorePch.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "argparse.hpp"
#include "random"
#include "Breakout.h"
#include "Macro.h"
#include "Objects.h"
#include "string.h"
#include "UiState.h"
#include "Client.h"
#include "ClientSession.h"
#include "Protocol.pb.h"
#include "BreakoutPacketHandler.h"
#include "DummySession.h"
#include "DummyPacketHandler.h"
#include "BufferReader.h"