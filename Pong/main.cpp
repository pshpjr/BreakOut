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
/*
 * TODO: 키보드 함수 변경
 * 지금은 딜레이 있으니까 keyboardfunc, keyboardupfunc 사용. 
 *
 */
void MySpecial(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_RIGHT:
		Breakout._control_block->setVector(pt(1, 0));
		Breakout._control_block->setSpeed(2);
		break;
	case GLUT_KEY_LEFT:
		Breakout._control_block->setVector(pt(-1, 0));
		Breakout._control_block->setSpeed(2);
		break;
	default:;
	}

	glutPostRedisplay();
}

void MyMouse(int button, int state, int x, int y) {

	glutPostRedisplay();
}

void MyMotion(int x, int y) {

	glutPostRedisplay();
}

void Render()
{
	Breakout.Render();
}

void Update()
{
	Breakout.Update();
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
	glutDisplayFunc(Update);
	glutMouseFunc(MyMouse);
	glutMotionFunc(MyMotion);
	glutSpecialFunc(MySpecial);
	
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	GameInit();
	GLInit();

	glutMainLoop();
	return 0;
}

