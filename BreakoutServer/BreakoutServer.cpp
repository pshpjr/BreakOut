#include "pch.h"

#include "ServerSession.h"
#include "ThreadManager.h"
#include "Service.h"
#include "argparse.hpp"
wstring ip = L"127.0.0.1";
uint16 port = 12321;

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


int main(int argc, char** argv)
{
	ArgParseInit(argc, argv);

	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(ip, port),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>, // TODO : SessionManager µî
		100);

	service->Start();

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