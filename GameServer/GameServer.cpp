﻿#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "Session.h"
#include "service.h"
#include "ThreadManager.h"

class GameSession : public Session
{
public:
	virtual int32 OnRecv(BYTE* buffer, int32 len) override
	{
		cout << "onRecv Len = " << len << endl;
		Send(buffer, len);
		return len;
	}
	void OnSend(int32 len) override
	{
		cout << "onSend Len = " << len << endl;
	}
};


int main()
{
	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>,
		100
		);

	ASSERT_CRASH(service->Start());

	for (int i = 0; i < 5; ++i)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}
	GThreadManager->Join();
}