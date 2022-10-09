#pragma once

#define WIN32_LEAN_AND_MEAN // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#ifdef _DEBUG
#pragma comment(lib, "Libs\\ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib, "Debug\\libprotobufd.lib")
#else
#pragma comment(lib, "Release\\ServerCore.lib")
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