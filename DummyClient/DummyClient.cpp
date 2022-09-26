﻿#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"



class ServerSession : public PacketSession
{
public:
	~ServerSession()
	{
		cout << "~ServerSession" << endl;
	}

	virtual void OnConnected() override
	{

	}

	virtual int32 OnRecvPacket(BYTE* buffer, int32 len) override
	{
		PacketHeader head = *(PacketHeader*)&buffer[0];
		//cout << "id: " << head.id << " size : " << head.size << endl;

		char recvBuffer[4096];
		::memcpy(recvBuffer, &buffer[4], head.size - sizeof(PacketHeader));
		cout << recvBuffer << endl;

		return len;
	}

	virtual void OnSend(int32 len) override
	{
	}

	virtual void OnDisconnected() override
	{
	}
};

int main()
{
	this_thread::sleep_for(1s);

	ClientServiceRef service = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>, // TODO : SessionManager 등
		1000);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 2; i++)
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