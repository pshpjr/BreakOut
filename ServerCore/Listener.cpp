#include "pch.h"
#include "Listener.h"
#include "SocketUtils.h"
#include "IocpEvent.h"
#include "Session.h"
#include "Service.h"


Listener::~Listener()
{
	SocketUtils::Close(_socket);

	for(AcceptEvent* acceptEvent : _acceptEvents)
	{

		xdelete(acceptEvent);
	}
}

bool Listener::StartAccept(ServerServiceRef service)
{
	_service = service;
	if (_service == nullptr)
		return false;

	_socket = SocketUtils::CreateSocket();
	if (_socket == INVALID_SOCKET)
		return false;
	if (service->GetIocpCore()->Register(shared_from_this()) == false)
		return false;

	if (SocketUtils::SetReuseAddress(_socket, true) == false)
		return false;

	if (SocketUtils::SetLinger(_socket, 0, 0) == false)
		return false;

	if (SocketUtils::Bind(_socket, service->GetNetAddress()) == false)
		return false;

	if (SocketUtils::Listen(_socket) == false)
		return false;

	//한 번만 이벤트 걸면 동접 문제가 생길 수 있음. 일단 패스

	const int32 acceptCount = _service->GetMaxSessionCount();
	for (int i = 0; i < acceptCount; ++i)
	{
		AcceptEvent* acceptEvent = xnew<AcceptEvent>();
		//레퍼런스 유지한 shared_ptr 생성. 
		acceptEvent->_owner = shared_from_this();
		_acceptEvents.push_back(acceptEvent);
		RegisterAccept(acceptEvent);
	}

	return true;

}

void Listener::CloseSocket()
{
	SocketUtils::Close(_socket);
}

HANDLE Listener::GetHandle()
{
	return reinterpret_cast<HANDLE>(_socket);
}

void Listener::Dispatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
	ASSERT_CRASH(iocpEvent->_eventType== EventType::Accept);

	AcceptEvent* acceptEvent = static_cast<AcceptEvent*>(iocpEvent);
	ProcessAccept(acceptEvent);
}

void Listener::RegisterAccept(AcceptEvent* acceptEvent)
{
	SessionRef session = _service->CreateSession();

	acceptEvent->Init();
	acceptEvent->_session= session;

	DWORD byteReceived = 0;
	/*비동기 accept. 리슨 소켓, 클라 소켓(미리 생성해야 함), 데이터 받을 버퍼,
	이 다음 인자는 0을 넣는데 이는 acceptEx에서 accept 후 데이터 수신도 동시에 진행하기 때문이다. 데이터를 받아 발생하는 문제가 있을 수 있고, 받는 작업은 다 recv에서 하고 싶기에
	0을 넣어준다. 값이 0이면 수신받지 않는다.
	뒤의 인자는 주소 + 16바이트 이상 쓰라고 msdn에 적혀있음.
	받은 데이터의 byte(안 씀)과 overlapped 객체*/
	if (false == SocketUtils::acceptEx(_socket,session->GetSocket(),session->_recvBuffer,0,
		sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16,
		OUT & byteReceived, static_cast<LPOVERLAPPED>(acceptEvent)))
	{
		const int32 errorCode = ::WSAGetLastError();
		if(errorCode != WSA_IO_PENDING)
		{
			RegisterAccept(acceptEvent);
		}
	}
}

void Listener::ProcessAccept(AcceptEvent* acceptEvent)
{
	SessionRef session = acceptEvent->_session;

	if(false == SocketUtils::SetUpdateAcceptSocket(session->GetSocket(),_socket))
	{
		RegisterAccept(acceptEvent);
		return;
	}

	SOCKADDR_IN sockAddress;
	int32 sizeofSockAddr = sizeof(sockAddress);
	//getpeername : 상대의 주소를 가지고 옴. 
	if (SOCKET_ERROR == ::getpeername(session->GetSocket(), OUT reinterpret_cast<SOCKADDR*>(&sockAddress), &sizeofSockAddr))
	{
		RegisterAccept(acceptEvent);
		return;
	}

	session->SetNetAddress(NetAddress(sockAddress));

	cout << "client Connected" << endl;

	RegisterAccept(acceptEvent);
}
