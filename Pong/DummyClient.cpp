#include "pch.h"
#include "DummyClient.h"

#include "DummyPlayer.h"
#include "DummyService.h"
#include "ThreadManager.h"

shared_ptr <DummyClient> DM;

enum
{
	WORKER_TICK = 16
};

DummyClient::DummyClient(wstring ip, int port,int count = 98) : _ip(ip), _port(port), dummyPlayers(count)
{
	JobQueue();

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
					LEndTickCount = psh::GetTickCount() + WORKER_TICK;

					_service->GetIocpCore()->Dispatch(10);

					ThreadManager::DistributeReservedJobs();

					ThreadManager::DoGlobalQueueWork();
				}
			});
	}
}

void DummyClient::Loop()
{
	auto start = psh::GetTickCount();
	
	Set<SessionRef> s = _service->getSessions();
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 3);
	P_Event("sessionRoof");
	for(auto ses : s)
	{
		int data = dis(gen);
		if(!data)
			continue;
		if(ses->IsConnected() ==false)
			continue;
		DummySessionRef session = static_pointer_cast<DummySession>(ses);

		switch(session->_owner->_state)
		{
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
			case LOBBY:
			{
				if (session->_owner->endCount !=10) {
					++session->_owner->endCount;
					break;
				}

				Protocol::C_MACHING_GAME pkt;
				SendBufferRef sb = DummyPacketHandler::MakeSendBuffer(pkt);
				session->Send(sb);
				session->_owner->_state = MATCHING;
				break;
			}
		}
	}
	auto end = psh::GetTickCount();


	if (end - start < 200)
		DoTimer(200 - (end - start), &DummyClient::Loop);
	else
		DoAsync(&DummyClient::Loop);
}

