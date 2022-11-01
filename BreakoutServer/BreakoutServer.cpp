#include "pch.h"

#include "ServerSession.h"
#include "ThreadManager.h"
#include "Service.h"
#include "argparse.hpp"
#include "RoomManager.h"

wstring ip = L"127.0.0.1";
uint16 port = 12321;

static bool run = true;

void ArgParseInit(int argc, char** argv)
{
	argparse::ArgumentParser program("Breakout");

	program.add_argument("-i")
		.help("IP")
		.default_value<std::string>(std::string{ "127.0.0.1" })
		.required()
		.nargs(1);

	program.add_argument("-p")
		.help("Port")
		.default_value<string>(std::string{ "12321" })
		.required()
		.nargs(1);

	try {
		program.parse_args(argc, argv);
	}
	catch (const std::runtime_error& err) {
		std::cerr << err.what() << std::endl;
		std::cerr << program;
		std::exit(1);
	}

	string p = program.get("-p");
	port = stoi(p);

	string tmp = program.get<std::string>("-i");
	ip.assign(tmp.begin(),tmp.end());
	
}

void MakeWorker(ServerServiceRef service)
{
	//TODO:dispatch 일정 시간 돌려보고 아니면 딴 일 하게 변경
	GThreadManager->Launch([=]()
		{
			P_THREAD("IOCPThread 1");
			while (run)
			{
				P_Event("Worker")
				service->GetIocpCore()->Dispatch(10);

				ThreadManager::DistributeReservedJobs();

				ThreadManager::DoGlobalQueueWork();
			}
		});

	GThreadManager->Launch([=]()
		{
			P_THREAD("IOCPThread 2");
			while (run)
			{
				P_Event("Worker")
				service->GetIocpCore()->Dispatch(3);

				ThreadManager::DistributeReservedJobs();

				ThreadManager::DoGlobalQueueWork();
			}
		});
	GThreadManager->Launch([=]()
		{
			P_THREAD("IOCPThread 3");
			while (run)
			{
				P_Event("Worker")
				service->GetIocpCore()->Dispatch(3);

				ThreadManager::DistributeReservedJobs();

				ThreadManager::DoGlobalQueueWork();
			}
		});
	GThreadManager->Launch([=]()
		{
			P_THREAD("IOCPThread 4");
			while (run)
			{
				P_Event("Worker")
				service->GetIocpCore()->Dispatch(3);

				ThreadManager::DistributeReservedJobs();

				ThreadManager::DoGlobalQueueWork();
			}
		});
	GThreadManager->Launch([=]()
		{
			P_THREAD("IOCPThread 5");
			while (run)
			{
				P_Event("Worker")
				service->GetIocpCore()->Dispatch(3);

				ThreadManager::DistributeReservedJobs();

				ThreadManager::DoGlobalQueueWork();
			}
		});
}

enum
{
	WORKER_TICK = 64
};

void WorkerJob(ServerServiceRef& service)
{

	while (true)
	{
		P_Event("Worker")
		LEndTickCount = ::GetTickCount64() + WORKER_TICK;

		service->GetIocpCore()->Dispatch(3);

		ThreadManager::DistributeReservedJobs();

		ThreadManager::DoGlobalQueueWork();


	}
}

int main(int argc, char** argv)
{
	OPTICK_APP("ConsoleApp");
	ArgParseInit(argc, argv);
	

	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(ip, port),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>, // TODO : SessionManager 등
		1000);

	cout << "server Start IP: " << std::string().assign(ip.begin(), ip.end()) << " Port : " << port << endl;
	service->Start();

	MakeWorker(service);

	for(auto& i :GRoomManager._rooms)
	{
		i->DoAsync(&Room::RoomCheck);
	}


	int32 Lcout = 0;
	while (true)
	{
		int32 now = GetTickCount();
		OPTICK_FRAME("MainThread");
		LEndTickCount = ::GetTickCount64() + WORKER_TICK;

		P_Event("Worker")
		service->GetIocpCore()->Dispatch(10);

		ThreadManager::DistributeReservedJobs();

		ThreadManager::DoGlobalQueueWork();

		P_Event("Sleep")
		this_thread::sleep_for(std::chrono::milliseconds(50 -(GetTickCount() - now)));
	}


	GThreadManager->Join();
}