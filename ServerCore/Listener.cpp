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



	const int32 acceptCount = _service->GetMaxSessionCount()/2;
	for (int i = 0; i < acceptCount; i++)
	{
		AcceptEvent* acceptEvent = xnew<AcceptEvent>();
		//���۷��� ������ shared_ptr ����. 
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
	/*�񵿱� accept. ���� ����, Ŭ�� ����(�̸� �����ؾ� ��), ������ ���� ����,
	�� ���� ���ڴ� 0�� �ִµ� �̴� acceptEx���� accept �� ������ ���ŵ� ���ÿ� �����ϱ� �����̴�. �����͸� �޾� �߻��ϴ� ������ ���� �� �ְ�, �޴� �۾��� �� recv���� �ϰ� �ͱ⿡
	0�� �־��ش�. ���� 0�̸� ���Ź��� �ʴ´�.
	���� ���ڴ� �ּ� + 16����Ʈ �̻� ����� msdn�� ��������.
	���� �������� byte(�� ��)�� overlapped ��ü*/
	if (false == SocketUtils::acceptEx(_socket,session->GetSocket(),session->_recvBuffer.WritePos(),0,
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
	SessionRef session = acceptEvent->_session;//acceptEvent�� ���� �����

	if(false == SocketUtils::SetUpdateAcceptSocket(session->GetSocket(),_socket))
	{
		RegisterAccept(acceptEvent);
		return;
	}

	SOCKADDR_IN sockAddress;
	int32 sizeofSockAddr = sizeof(sockAddress);
	//getpeername : ����� �ּ�(Ŭ�� �ּ�)�� sockAddr�� ����
	if (SOCKET_ERROR == ::getpeername(session->GetSocket(), OUT reinterpret_cast<SOCKADDR*>(&sockAddress), &sizeofSockAddr))
	{
		//�� Ŭ�� ���� �۾��ϴ� �������� Accept�� �ɾ���� �� �̺�Ʈ���� ��� accept ó�� ����
		RegisterAccept(acceptEvent);
		return;
	}

	session->SetNetAddress(NetAddress(sockAddress));
	/*������ �������(�����ٸ�) ���� ���� �� ���� ������ �Լ��� ȣ���Ѵ�.(onConnected)
	 *���� �ڵ� �������� Register �̿��� �񵿱� ����ϰ�, �Ϸ�Ǹ� Process ȣ���ϴ� �������� ����. 
	 */

	session->ProcessConnect();
	//�̺�Ʈ�� ��� ���� ��
	RegisterAccept(acceptEvent);
}
