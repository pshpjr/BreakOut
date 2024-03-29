﻿#include "pch.h"
#include "functional"
#include "Service.h"
#include "Session.h"
#include "ThreadManager.h"
#include "fstream"
#include <random>
#include <string>
#include "BreakoutPacketHandler.h"
#include "DummyClient.h"

bool noGUI = false;
bool Exit = false;
string key;
ClientServiceRef _service;
wstring ip = L"127.0.0.1";
uint16 port = 12321;

int playerCount = 99;

int tmp = 0;

void HideCMD(bool isHide)
{
	HWND hWnd = GetForegroundWindow();
	isHide ? ShowWindow(hWnd, SW_SHOW) : ShowWindow(hWnd, SW_HIDE);
}

bool GameInit()
{
	cout << "Dummy Start IP: " << std::string().assign(ip.begin(), ip.end()) << " Port : " << port << endl;
	DM = MakeShared<DummyClient>(ip, port, playerCount);
	return true;
}
void idle()
{
	glutPostRedisplay();
}



void ArgParseInit(int argc, char** argv)
{
	argparse::ArgumentParser program("Breakout");

	program.add_argument("-noGUI")
		.help("GUI Setting")
		.default_value(false)
		.implicit_value(true);

	program.add_argument("-d")
		.help("Dummy client enable")
		.default_value(false)
		.implicit_value(true);

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

	program.add_argument("-c")
		.help("DummyCount")
		.default_value<string>(std::string{ "98" })
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

	if (program["-noGUI"] == true)
	{
		noGUI = true;
		cout << "noGUI Enabled" << endl;
	}

	string p = program.get("-p");
	port = stoi(p);

	string tmp = program.get<std::string>("-i");
	ip.assign(tmp.begin(), tmp.end());

	auto i = program.get("-c");
	playerCount = stoi(i );
}

int main(int argc, char** argv) {
	OPTICK_APP("DUMMYCLIENT")
	ArgParseInit(argc, argv);

	if (GameInit() == false)
		return 0;

	DM->Loop();
	


	GThreadManager->Join();
	return 0;
}

