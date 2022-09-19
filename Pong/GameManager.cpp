#include "pch.h"
#include "GameManager.h"

#include <WinSock2.h>
#include <WS2tcpip.h>

void Init()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return;

	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
		return;

	u_long on =1;
	if (::ioctlsocket(clientSocket, FIONBIO, &on) == INVALID_SOCKET)
		return;

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
}


GameManager::GameManager()
{
	_pongs.reserve(99);

}



void GameManager::AddPong(int32 width, int32 height, int32 x, int32 y)
{
	_pongs.emplace_back(width, height, x, y);
}

void GameManager::Tick()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (_noGUI) {
		cout << "ticked" << endl;

		for (auto& i : _pongs) {
			i.Tick();
		}
		return;
	}

	for (auto& i : _pongs) {
		i.Tick();
	}
	glutSwapBuffers();
	glutPostRedisplay();
}

void GameManager::AddPong(int32 width, int32 height, int32 x, int32 y,char L, char R)
{
	_pongs.emplace_back(width,height,x,y,L,R);
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
		i.noGUI = value;
	}
}
