#include "pch.h"
#include "DummyClient.h"
#include "Service.h"
#include "ThreadManager.h"
DummyClient::DummyClient(wstring ip, int port) : _ip(ip), _port(port)
{
	_service = MakeShared<ClientService>(
		NetAddress(_ip, _port),
		MakeShared<IocpCore>(),
		MakeShared<DummySession>, // TODO : SessionManager 등
		98);

	_service->Start();

	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					_service->GetIocpCore()->Dispatch();
				}
			});
	}

}

void DummyClient::Loop()
{
	for(auto i :_service->getSessions())
	{
		DummySessionRef session = static_pointer_cast<DummySession>(i);
		if(session->_state == PLAYING)
		{
			Protocol::KeyInput* key = new Protocol::KeyInput;
			Protocol::C_MOVE pkt;

			key->set_direction(rand()%2);
			key->set_onoff(session->onOff);

			session->onOff = !session->onOff;

			pkt.set_allocated_input(key);

			SendBufferRef buffer = BreakoutPacketHandler::MakeSendBuffer(pkt);

			_service->Broadcast(buffer);
		}
	}
}

