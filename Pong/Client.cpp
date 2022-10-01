#include "pch.h"
#include "Client.h"
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "ClientSession.h"
#include "Service.h"
#include "ThreadManager.h"

ClientPtr GM;

bool Client::Init()
{
	_state = Lobby::instance();
	this_thread::sleep_for(1s);
	_service = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ClientSession>, // TODO : SessionManager ��
		1);

	_service->Start();

	for (int32 i = 0; i < 2; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (!_exit)
				{
					_service->GetIocpCore()->Dispatch();
				}
			});
	}


	return true;
}

bool Client::ProcessInput(float dt)
{
	float velocity = 1 * dt;
	// move playerboard
	_state->HandleInput(this);
	
	if (isKeyPressing(VK_ESCAPE)) {
		return false;
	}
	return true;
}



Client::Client(int32 SCREEN_WIDTH, int32 SCREEN_HEIGHT) :SCREENWIDTH(SCREEN_WIDTH),SCREENHEIGHT(SCREEN_HEIGHT)
{
	_pongs.reserve(99);
	Init();
	int width = SCREEN_WIDTH / 3;
	int mWidth = width / 7;
	int mHeight = SCREEN_HEIGHT / 7;


	AddPong(width, SCREEN_HEIGHT, width, 0);
	_mainPlay = _pongs[0];
	_mainPlay->_isMyPlay = true;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			AddPong(mWidth, mHeight, j * mWidth, i * mHeight);
		}
	}
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			AddPong(mWidth, mHeight, j * mWidth + width * 2, i * mHeight, 'j', 'l');
		}
	}
}

void Client::AddPong(int32 width, int32 height, int32 x, int32 y)
{
	_pongs.push_back(make_shared<Breakout>(width, height, x, y));
}

bool Client::Tick()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (false == ProcessInput(10))
		return false;
	_state->HandleInput(this);

	if (_noGUI)
		return true;

	_state->Render(this);

	glutSwapBuffers();
	glutPostRedisplay();
	return true;
}

void Client::AddPong(int32 width, int32 height, int32 x, int32 y,char L, char R)
{
	_pongs.push_back(make_shared<Breakout>(width, height, x, y, L, R));
	
}

void Client::Start()
{
	while (Tick())
	{
		this_thread::sleep_for(16.6ms);
	}
}

void Client::End()
{
	_exit = true;
}

void Client::noGUI(bool value)
{
	_noGUI = value;
	for (auto& i : _pongs) {
		i->noGUI = value;
	}
}
