#include "pch.h"
#include "functional"



/*TODO: ��ǥ ó�� ������ ��ȯ*/

int WINDOWSIZE = 100;
int MAPSIZE = WINDOWSIZE - 20;

const int32 SCREEN_WIDTH = 800;
const int32 SCREEN_HEIGHT = 600;

Pong Breakout(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOWSIZE);

double BALLSIZE = 2.5;

bool DEBUG = TRUE;

//�ڽ��� �׻� ���ϴ� ��ǥ�� start�� ���� ��

void my_reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
/*
 * TODO: Ű���� �Լ� ����
 * ������ ������ �����ϱ� keyboardfunc, keyboardupfunc ���. 
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

