#include "pch.h"
#include "GameManager.h"

#include <WinSock2.h>
#include <WS2tcpip.h>

bool GameManager::Init()
{
	cout << "SocketInit " << endl;
	_state = Lobby::instance();
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return false;

	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
		return false;

	u_long on =1;
	if (::ioctlsocket(clientSocket, FIONBIO, &on) == INVALID_SOCKET)
		return false;

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = ::htons(7777);

	// Connect
	while (true)
	{
		if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		{
			// 원래 블록했어야 했는데... 너가 논블로킹으로 하라며?
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			// 이미 연결된 상태라면 break
			if (::WSAGetLastError() == WSAEISCONN)
				break;
			// Error
			break;
		}
	}
	cout << "ServerConnected " << endl;
	return true;
}

void GameManager::ProcessInput(float dt)
{
	float velocity = 1 * dt;
	// move playerboard
	_state->HandleInput(this);
	
	if (isKeyPressing(VK_ESCAPE))
		exit(0);
}



GameManager::GameManager(int32 SCREEN_WIDTH, int32 SCREEN_HEIGHT)
{
	_pongs.reserve(99);
	Init();
	int width = SCREEN_WIDTH / 3;
	_width = width;
	_height = SCREEN_HEIGHT;
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

void GameManager::AddPong(int32 width, int32 height, int32 x, int32 y)
{
	_pongs.push_back(make_shared<Breakout>(width, height, x, y));
}

void GameManager::Tick()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ProcessInput(10);
	_state->HandleInput(this);

	if (_noGUI)
		return;

	_state->Render(this);

	glutSwapBuffers();
	glutPostRedisplay();
}

void GameManager::AddPong(int32 width, int32 height, int32 x, int32 y,char L, char R)
{
	_pongs.push_back(make_shared<Breakout>(width, height, x, y, L, R));
	
}

void GameManager::Start()
{
	while (true)
	{
		Tick();
		this_thread::sleep_for(16.6ms);
	}
}

void GameManager::noGUI(bool value)
{
	_noGUI = value;
	for (auto& i : _pongs) {
		i->noGUI = value;
	}
}
