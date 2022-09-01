#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"

#include <WinSock2.h>
#include <mswsock.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
	{
		int32 errorCode = ::WSAGetLastError();
		cout << errorCode << endl;
		return 0;
	}

	//내 주소는?
	SOCKADDR_IN serverAddr = {};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(7777);

	if(::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		cout << "bind error : " << WSAGetLastError() << endl;
	}

	if(::listen(listenSocket, 10) == SOCKET_ERROR)
	{
		cout << "Listen error : " << WSAGetLastError() << endl;
	}

	while (true)
	{
		SOCKADDR_IN clientAddr = {};
		int32 addrLen = sizeof(clientAddr);
		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
		if(clientSocket == INVALID_SOCKET)
		{
			cout << "Client Socket error : " << WSAGetLastError() << endl;
		}

		char ipAddr[16];
		::inet_ntop(AF_INET, &clientAddr.sin_addr, ipAddr, sizeof(ipAddr));
		cout << "Client Connected. IP : " << ipAddr << endl;


		
		while (true)
		{
			char sendBuffer[100];
			int recvLen= ::recv(clientSocket, sendBuffer, sizeof(sendBuffer), 0);

			if(recvLen <=0)
			{
				cout << "Receive error : " << WSAGetLastError() << endl;
			}

			cout << "Data : " << sendBuffer << endl;
			cout << "Len : " << recvLen << endl;

			//에코 서버 코드
			if (::send(clientSocket, sendBuffer, (int)sizeof(sendBuffer), 0) == SOCKET_ERROR)
			{
				cout << "SendError: " << WSAGetLastError() << endl;
				return 0;
			}

			else
				cout << "send Data len : " << sizeof(sendBuffer) << endl;

			this_thread::sleep_for(1s);
		}
	}


	::WSACleanup();
}