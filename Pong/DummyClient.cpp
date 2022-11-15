#include "pch.h"
#include "DummyClient.h"

#include "DummyPlayer.h"
#include "DummyService.h"
#include "ThreadManager.h"

DummyClient::DummyClient(wstring ip, int port,int count = 98) : _ip(ip), _port(port), dummyPlayers(count)
{
	_service = MakeShared<DummyService>(
		NetAddress(_ip, _port),
		MakeShared<IocpCore>(),
		MakeShared<DummySession>, // TODO : SessionManager 등
		count);

	_service->Start();

	for (int32 i = 0; i < 6; i++)
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
	Set<SessionRef>& s = _service->getSessions();
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 3);
	P_Event("sessionRoof");
	for(auto& ses : s)
	{
		int data = dis(gen);
		if(!data)
			continue;
		if(ses->IsConnected() ==false)
			continue;
		DummySessionRef session = static_pointer_cast<DummySession>(ses);

		switch(session->_owner->_state)
		{
			case LOBBY:
			{
				Protocol::C_MACHING_GAME pkt;
				SendBufferRef sb = DummyPacketHandler::MakeSendBuffer(pkt);
				session->Send(sb);

				break;
			}
			case PLAYING:
			{
				Protocol::KeyInput* key = new Protocol::KeyInput;
				Protocol::C_MOVE pkt;

				key->set_direction(rand() % 2);
				key->set_onoff(session->_owner->onOff);

				session->_owner->onOff = !session->_owner->onOff;

				pkt.set_allocated_input(key);
				pkt.set_roomnumber(session->_owner->roomNumber);
				SendBufferRef buffer = BreakoutPacketHandler::MakeSendBuffer(pkt);

				session->Send(buffer);

				break;
			}

		}


	}
}

