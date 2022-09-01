#include "pch.h"
#include <iostream>

#include <WinSock2.h>
#include <mswsock.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	//winsock lib 초기화(ws2_32.lib 초기화)
	//관련 정보가 wsaData에 저장. 사용하진 않음.
	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	//소문자 함수는 리눅스에서도 작동할 확률이 높음.

	//인자(af(address family(주소 체계)),type(tcp,udp여부 stream = tcp, dgram = udp),protocol(0이 default ) 
	//return : descripter

	SOCKET ClientSocket = ::socket(AF_INET,SOCK_STREAM,0);

	if(ClientSocket == INVALID_SOCKET)
	{
		int32 errorCode = ::WSAGetLastError();
		cout << errorCode << endl;
		return 0;
	}

	//연결 목적지는?
	//1)  sockaddr in을 만들고, 0으로 초기화 후, sin family, sin addr, sin port를 결정)

	SOCKADDR_IN serverAddr;// ipv4를 사용할 땐 이거 v6는 딴 거 씀
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

	//연결 목적지  = ip + 포트 쌍
	//host to network short 함수 사용 이유
	//리틀 엔디안, 빅 엔디안 이슈가 있어서
	//리틀 엔디안은 1바이트씩 역으로 빅 엔디안은 정상적으로
	//cpu마다 사용 엔디안이 다르기에 (보통은 리틀)
	//네트워크에선 빅엔디안을 사용하는게 문제
	//빅 엔디안으로 변환해서 전송함. 
	serverAddr.sin_port = ::htons(7777);


	//왜 캐스팅해야 하는가? IPv4를 채우기 위해 SockaddrIn을 썼지만 다른 방식으로 만들수도 있기에 캐스팅, 크기도 넣어야 함
	if(::connect(ClientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		cout << WSAGetLastError() << endl;
	}

	cout << "Connected" << endl;

	char sendBuffer[100] = "Hello World";

	while (true)
	{// 버퍼를 다 보낼지 데이터만 보낼지 정할 수 있음.
		if(	::send(ClientSocket, sendBuffer, (int)sizeof(sendBuffer), 0) == SOCKET_ERROR)
		{
			cout << "SendError: "<<WSAGetLastError() << endl;
			return 0;
		}

		else
			cout << "send Data len : " << sizeof(sendBuffer) << endl;


		int recvLen = ::recv(ClientSocket, sendBuffer, sizeof(sendBuffer), 0);

		if (recvLen <= 0)
		{
			cout << "Receive error : " << WSAGetLastError() << endl;
		}

		cout << "Data : " << sendBuffer << endl;
		cout << "Len : " << recvLen << endl;
		this_thread::sleep_for(1s);
	}


	closesocket(ClientSocket);


	WSACleanup();//wsa startup 호출된만큼 실행
	

}