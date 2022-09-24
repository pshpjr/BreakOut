#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"

char sendBuffer[] = "1";
class GameSession : public Session
{
public:
	~GameSession()
	{
		cout << "~GameSession" << endl;
	}
	virtual void OnConnected() override
	{
		cout << "ClientAdded" << endl;
		Send((BYTE*)sendBuffer, len32(sendBuffer));
	}
	virtual int32 OnRecv(BYTE* buffer, int32 len) override
	{
		// Echo
		cout << "OnRecv Len = " << len << endl;
		Send(buffer, len);
		return len;
	}

	virtual void OnSend(int32 len) override
	{
		this_thread::sleep_for(3s);
		cout << "OnSend Len = " << len << endl;
		Send((BYTE*)sendBuffer, len32(sendBuffer));
	}
};

int main()
{
	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>, // TODO : SessionManager µî
		100);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 5; i++)
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