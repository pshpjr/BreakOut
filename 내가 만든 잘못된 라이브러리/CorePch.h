#pragma once

#include "optick.h"
#include "Types.h"
#include "CoreMacro.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"
#include "Container.h"

#include <windows.h>
#include <iostream>
using namespace std;

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "Lock.h"
#include "ObjectPool.h"
#include "Memory.h"
#include "SendBuffer.h"
#include "JobQueue.h"

#include "Session.h"



namespace psh
{
	template <typename T = chrono::milliseconds>
	inline unsigned long long GetTickCount()
	{
		using namespace std::chrono;
		return duration_cast<T>(steady_clock::now().time_since_epoch()).count();
	}
}