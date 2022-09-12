#include "pch.h"
#include "functional"



/*TODO: 좌표 처리 정수로 변환*/



int WINDOWSIZE = 100;


int32 SCREEN_WIDTH = 800;
int32 SCREEN_HEIGHT = 600;

GameManager GM;



bool DEBUG = TRUE;

//박스는 항상 좌하단 좌표를 start로 넣을 것

void my_reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void MyMouse(int button, int state, int x, int y) {
}

void MyMotion(int x, int y) {
}

void GetMonitorResolution(OUT int& width, OUT int& height)
{
#ifdef _WIN32
	MONITORINFO target;
	target.cbSize = sizeof(target);
	HMONITOR Hmon = MonitorFromWindow(GetDesktopWindow(), MONITOR_DEFAULTTOPRIMARY);
	GetMonitorInfo(Hmon, &target);

	width = target.rcMonitor.right;
	height = target.rcMonitor.bottom;
#elif __linux__

#endif

}

void GLInit() {
	GetMonitorResolution(SCREEN_WIDTH, SCREEN_HEIGHT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Pong Loader");
	glOrtho(-WINDOWSIZE, WINDOWSIZE, -WINDOWSIZE, WINDOWSIZE, -WINDOWSIZE, WINDOWSIZE);
	glutDisplayFunc([]() {
			GM.Tick();
		});
	glutKeyboardFunc([](unsigned char key, int x, int y) {
		for(auto& i : GM._pongs)
		{
			i.Keys[key] = true;
		}
		});
	glutKeyboardUpFunc([](unsigned char key, int x, int y) {
		for (auto& i : GM._pongs)
		{
			i.Keys[key] = false;
		}
		});

	glDisable(GL_LIGHTING);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	GLInit();

	GM.AddPong(SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0, 0, WINDOWSIZE,'a','d');
	GM.AddPong(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH / 2, 0, WINDOWSIZE,'j','l');
	for (auto& i : GM._pongs)
	{
		i.changeState(Pong::GAME_ACTIVE);
	}


	glutMainLoop();
	return 0;
}

