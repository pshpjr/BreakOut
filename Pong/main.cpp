#include "pch.h"
#include "functional"



/*TODO: ��ǥ ó�� ������ ��ȯ*/



int WINDOWSIZE = 100;


int32 SCREEN_WIDTH = 800;
int32 SCREEN_HEIGHT = 600;

GameManager GM;



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


void MyMouse(int button, int state, int x, int y) {
}

void MyMotion(int x, int y) {
}

void GLInit() {
	SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Pong Loader");
	glutFullScreen();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
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

	int width = SCREEN_WIDTH / 3;
	int mWidth = width / 7;
	int mHeight = SCREEN_HEIGHT / 7;


	GM.AddPong(width, SCREEN_HEIGHT, width, 0);
	GM._pongs[0]._isMyPlay = true;

	for(int i = 0; i <7;i++)
	{
		for (int j = 0; j < 7; j++)
		{
			GM.AddPong(mWidth, mHeight, j * mWidth, i * mHeight);
		}
	}
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			GM.AddPong(mWidth, mHeight, j * mWidth + width*2, i * mHeight,'j','l');
		}
	}



	for (auto& i : GM._pongs)
	{
		i.changeState(Pong::GAME_ACTIVE);
	}


	glutMainLoop();
	return 0;
}

