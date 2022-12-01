#include "pch.h"
#include "functional"
#include "Service.h"
#include "Session.h"
#include "ThreadManager.h"
#include "fstream"
#include <random>
#include <string>
#include "BreakoutPacketHandler.h"
class ServerSession;

bool noGUI = false;
bool Exit = false;
string key;
ClientServiceRef _service;
wstring ip = L"127.0.0.1";
uint16 port = 12321;

int WINDOWSIZE = 100;

int32 SCREEN_WIDTH = 800;
int32 SCREEN_HEIGHT = 600;

char sendData[] = "Hello World";

int tmp = 0;

void HideCMD(bool isHide)
{
	HWND hWnd = GetForegroundWindow();
	isHide ? ShowWindow(hWnd, SW_SHOW) : ShowWindow(hWnd, SW_HIDE);
}


void my_reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


bool GameInit()
{
	GM = make_shared<Client>(SCREEN_WIDTH, SCREEN_HEIGHT,ip,port);

	GM->noGUI(noGUI);


	return true;
}
void idle()
{
	glutPostRedisplay();
}



static int tickCount = 0;
void tick(int time)
{
	uint64 start = psh::GetTickCount();
	GM->Tick();
	tickCount++;

	auto now = psh::GetTickCount();
	auto dur = now - start;

	if (dur < 10)
		glutTimerFunc(10 - dur, tick, 0);
	else
		glutTimerFunc(0, tick, 0);
}

void GLInit() {
	SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT)/2;
	SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH)/2;



	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutIdleFunc(idle);

	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);

	glDisable(GL_LIGHTING);

	glutCreateWindow("Breakout 99");
	//glutFullScreen();
	glutDisplayFunc(idle);

	glutTimerFunc(1, tick, 0);
	glutSetCursor(GLUT_CURSOR_NONE);

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

	string p = program.get("-p");
	port = stoi(p);

	string tmp = program.get<std::string>("-i");
	ip.assign(tmp.begin(), tmp.end());
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



	glutMainLoop();




	GThreadManager->Join();
	return 0;
}

