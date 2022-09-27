#include "pch.h"
#include "functional"
#include "Service.h"
#include "Session.h"
#include "ThreadManager.h"
#include "fstream"
#include <random>
#include <string>
ClientPtr GM;

bool noGUI = false;
bool Exit = false;
string key;
class ServerSession : public Session
{
public:
	~ServerSession()
	{
		cout << "~ServerSession" << endl;
	}

	virtual void OnConnected() override
	{
		cout << "Connected To Server" << endl;
	}

	virtual int32 OnRecv(BYTE* buffer, int32 len) override
	{
		cout << "OnRecv Len = " << len << endl;

		this_thread::sleep_for(1s);
		string s = (char*)buffer;
		int i = stoi(s);
		if (GM->_state == Playing::instance()) {
			GM->_mainPlay->_control_block->setVector({i,0 });
			GM->_mainPlay->_control_block->setSpeed(GM->CONTROLBLOCKSPEED);
		}

		return len;
	}

	virtual void OnSend(int32 len) override
	{
		cout << "OnSend Len = " << len << endl;
	}

	virtual void OnDisconnected() override
	{
		cout << "Disconnected" << endl;
	}
};

/*TODO: 좌표 처리 정수로 변환*/

void HideCMD(bool isHide)
{
	HWND hWnd = GetForegroundWindow();
	isHide ? ShowWindow(hWnd, SW_SHOW) : ShowWindow(hWnd, SW_HIDE);
}

int WINDOWSIZE = 100;

int32 SCREEN_WIDTH = 800;
int32 SCREEN_HEIGHT = 600;



//박스는 항상 좌하단 좌표를 start로 넣을 것


std::string random_string(std::string::size_type length)
{
	static auto& chrs = "0123456789"
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	thread_local static std::mt19937 rg{ std::random_device{}() };
	thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

	std::string s;

	s.reserve(length);

	while (length--)
		s += chrs[pick(rg)];

	return s;
}

void my_reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

string GetKey()
{
	string key;
	std::ifstream fin("key.txt");

	if (fin.fail())
	{
		std::ofstream fout("key.txt");
		key = random_string(5);

		fout << key;
		fout.close();

		return key;
	}

	fin >> key;

	fin.close();

	return key;
}

bool GameInit()
{
	key = GetKey();
	GM = make_shared<Client>(SCREEN_WIDTH, SCREEN_HEIGHT);

	GM->noGUI(noGUI);

	this_thread::sleep_for(1s);

	ClientServiceRef service = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>, // TODO : SessionManager 등
		1);

	if(service->Start() == false)
	{
		cout << "Cannot Connect to Server" << endl;
		return false;
	}

	for (int32 i = 0; i < 2; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (!Exit)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}
	return true;
}

void GLInit() {
	SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(0, 0);

	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
	//string s = SCREEN_WIDTH + "x" + SCREEN_HEIGHT;
	//glutGameModeString(s.c_str());
	//if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
	//	glutEnterGameMode();
	glDisable(GL_LIGHTING);

	glutCreateWindow("Breakout 99");
	//glutSetCursor(GLUT_CURSOR_NONE);
	//glutFullScreen();
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
	//TODO: 사람 수 인자로 받게

	try {
		program.parse_args(argc, argv);
	}
	catch (const std::runtime_error& err) {
		std::cerr << err.what() << std::endl;
		std::cerr << program;
		std::exit(1);
	}

	if(program["-noGUI"] == true)
	{
		noGUI = true;
		cout << "noGUI Enabled" << endl;
	}

}


int main(int argc, char** argv) {
	ArgParseInit(argc, argv);
	//HideCMD(noGUI);

	if (noGUI == false) {
		glutInit(&argc, argv);
		GLInit();
	}
	if (GameInit() == false)
		return 0;

	GM->Start();
	
	Exit = true;
	GThreadManager->Join();
	return 0;
}

