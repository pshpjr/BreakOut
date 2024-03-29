#include "pch.h"

#include "ServerSession.h"
#include "ThreadManager.h"
#include "Service.h"
#include "argparse.hpp"
#include "RoomManager.h"

wstring ip = L"127.0.0.1";
uint16 port = 12321;

static bool run = true;
enum
{
	WORKER_TICK = 16
};
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

void WorkerJob(ServerServiceRef& service)
{

	while (true)
	{
		
		LEndTickCount = psh::GetTickCount() + WORKER_TICK;

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
		MakeShared<ServerSession>, // TODO : SessionManager ��
		1000);

	cout << "server Start IP: " << std::string().assign(ip.begin(), ip.end()) << " Port : " << port << endl;
	service->Start();

	for (int i = 0; i < 16; ++i)
	{
		GThreadManager->Launch([=]()
			{
				P_THREAD("IOCPThread");
				while (run)
				{
					LEndTickCount = psh::GetTickCount() + WORKER_TICK;
					service->GetIocpCore()->Dispatch(1);

					ThreadManager::DistributeReservedJobs();

					ThreadManager::DoGlobalQueueWork();
				}
			});
	}

	int time = 0;

	//GRoomManager._rooms[0]->DoTimer(15, &Room::RoomCheck);
	GRoomManager->Init();

	int32 Lcout = 0;
	while (true)
	{
		int32 now = psh::GetTickCount();
		OPTICK_FRAME("MainThread");
		LEndTickCount = psh::GetTickCount() + WORKER_TICK;

		service->GetIocpCore()->Dispatch(3);

		ThreadManager::DistributeReservedJobs();

		ThreadManager::DoGlobalQueueWork();

		int32 sleep = psh::GetTickCount() - now;
		if(50>sleep)
			this_thread::sleep_for(chrono::milliseconds(50 - sleep));
	}


	GThreadManager->Join();
}