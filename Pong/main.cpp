#include "pch.h"
#include "functional"



/*TODO: 좌표 처리 정수로 변환*/

int WINDOWSIZE = 100;
int MAPSIZE = WINDOWSIZE - 20;

const int32 SCREEN_WIDTH = 800;
const int32 SCREEN_HEIGHT = 600;

Pong Breakout(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOWSIZE);

double BALLSIZE = 2.5;

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

void KeyDown(unsigned char key, int x, int y)
{
	Breakout.Keys[key] = true;
}

void KeyUp(unsigned char key, int x, int y)
{
	Breakout.Keys[key] = false;
}


void MyMouse(int button, int state, int x, int y) {

	glutPostRedisplay();
}

void MyMotion(int x, int y) {

	glutPostRedisplay();
}

void Tick()
{
	Breakout.tick();
}

void GameInit()
{
	Breakout.Init();
}

void GLInit() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Pong Loader");
	glOrtho(-WINDOWSIZE, WINDOWSIZE, -WINDOWSIZE, WINDOWSIZE, -WINDOWSIZE, WINDOWSIZE);
	glutDisplayFunc(Tick);
	glutMouseFunc(MyMouse);
	glutMotionFunc(MyMotion);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glDisable(GL_LIGHTING);
	
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	GameInit();
	GLInit();

	glutMainLoop();
	return 0;
}

