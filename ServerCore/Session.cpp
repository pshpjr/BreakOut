#include "pch.h"
#include "Session.h"
#include "Service.h"
#include "SocketUtils.h"

	/*Session*/
Session::Session()
{
	_socket = SocketUtils::CreateSocket();
}

Session::~Session()
{
	SocketUtils::Close(_socket);
}

void Session::Send(BYTE* buffer, int32 len)
{
	//temp
	SendEvent* sendEvent = xnew<SendEvent>();
	sendEvent->_owner = shared_from_this();

	sendEvent->buffer.resize(len);
	::memcpy(sendEvent->buffer.data(), buffer, len);


	WRITE_LOCK
	RegisterSend(sendEvent);
}

//Q. send ����߿� Ŭ�� ������ �������� ���� session ��ü�� ��� ���� ��.
// �� ��Ȳ���� _socket ��ü�� ������ٸ�?
//session�� ��� �ְ����� Iocp ���ο��� send ������ ���� ������?
//Recv�� Recv ���� �Ŀ� Disconnect �ϴϱ� ���� ���� �� ������
void Session::Disconnect(const WCHAR* cause)
{
	//exchange : �����غ���. ���� ���̶� ���� ���̶� ������ false�� ����
	//���°� false�� �� �н�
	if (_connected.exchange(false) == false)
		return;

	//true�� �� ����

	//temp

	wcout << "Disconnect : " << cause << endl;

	OnDisConnected();

	//���� �ݰ� ���� release �ϸ� refcount�� ����. ���� event�� �ɷ� ���� �ʴٸ� ������
	SocketUtils::Close(_socket);
	GetService()->ReleaseSession(GetSessionRef());

	
}

void Session::RegisterConnect()
{


}

void Session::RegisterRecv()
{
	//���� Ȯ��
	if (IsConnected() == false)
		return;

	//recv�� ���� overlapped �ʱ�ȭ �� ���, recv ȣ��

	//recvEvent�� ������ �ִ� ��(�� ������ ��) �� ������ �������� �ʴ´�.
	_recvEvent.Init();
	_recvEvent._owner = shared_from_this();

	//�̺�Ʈ ���ο� �־ �ǰ� ���ÿ��� ���� �ȴ�. ��� �� ��ü�� �� �Ѱ��� �� ���� _recvBuf �Ҹ길 �� �Ǹ� ��� xx
	WSABUF wsaBuf;
	wsaBuf.buf = reinterpret_cast<char*>(_recvBuffer);
	wsaBuf.len = len32(_recvBuffer);

	DWORD numOfBytes = 0;
	DWORD flags = 0;

	if (SOCKET_ERROR == WSARecv(_socket, &wsaBuf, 1, &numOfBytes, &flags, &_recvEvent, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if(errorCode != WSA_IO_PENDING)
		{
			//���� ó����
			HandleError(errorCode);

			//�ʱ�ȭ �� ���ָ� Iocp�� �Ϸ� ������ ���� �����Ŷ� ��� ������� ��
			//�� ���� �����ؾ� ��
			_recvEvent._owner = nullptr;

		}
	}
	
}

void Session::RegisterSend()
{
}

//sendEvent�� �ɹ��� ������ ���� �����ϱ� �ϴ� �Ѱ��ִ� ���� �ӽ÷� ����� ���
void Session::RegisterSend(SendEvent* sendEvent)
{
	//send�� �ܰ躰�� ������ �� �ְ� �ӽ� �ڵ尡 ����.
	//�׷��� �������� ���� ������ �� �ִ�.

	if (IsConnected() == false)
		return;

	WSABUF wsabuf;
	wsabuf.buf = (char*)sendEvent->buffer.data();
	wsabuf.len = (ULONG)sendEvent->buffer.size();

	DWORD numOfBytes = 0;

	if(SOCKET_ERROR == ::WSASend(_socket, &wsabuf, 1, OUT & numOfBytes, 0, sendEvent, nullptr))
	{
		int32 errorCode = WSAGetLastError();
		if(errorCode != WSA_IO_PENDING)
			HandleError(errorCode);
		sendEvent->_owner = nullptr;
		xdelete(sendEvent);
	}
}

void Session::ProcessConnect()
{
	_connected = true;

	//���� ���
	GetService()->AddSession(GetSessionRef());

	//���������� �����ε�
	OnConnect();

	//���� ���

	RegisterRecv();
}

void Session::ProcessRecv(int32 numOfBytes)
{
	//��¥�� event�� ���� ���ǵ� owner�� �� ������ ���� ������?
	//�����ֱ⸦ ��Ȯ�ϰ� �����ϱ� ����. ���� �����ڿ��� ������ٰ� �ϸ�
	//owner�� ���� ������ �Ǵ��� �ָ��ϴ�.
	//wsaRecv�� ȣ���� �Ŀ��� ������ �� ��.
	//�׷��� ��Ȯ�ϰ� �ϱ� ���� ����� �� �ø��� ����, �Ϸ�� ���̴� ���·�
	//������ ���۷��� ī������ �̻�����. 

	_recvEvent._owner = nullptr;//recv �޾����ϱ� �о ��. ������ recvEvent�� ����� ������ ����. ���߿� send�� �߰��� ��
	//�޴� �� �ѱ����� ��� �޾Ƶ� ������ �����°� ���� �� ���� �� �����ٵ�
	//���� �����δ� �ָ�������

	if(numOfBytes == 0)
	{
		Disconnect(L"Recv 0");
		return;
	}

	OnRecv(_recvBuffer,numOfBytes);

	//���� ���. ������ �� �� �ٽ� �޴´ٰ� �ؾ� ��. 
	RegisterRecv();
}

void Session::ProcessSend(int32 numOfBytes)
{
}

//Temp
void Session::ProcessSend(SendEvent* sendEvent, int32 numOfBytes)
{
	sendEvent->_owner = nullptr;
	xdelete(sendEvent);

	if(numOfBytes == 0)
	{
		Disconnect(L"send 0");
		return;
	}
	OnSend(numOfBytes);
}

void Session::HandleError(int32 errorCode)
{
	switch (errorCode)
	{
	case WSAECONNRESET:
	case WSAECONNABORTED:
		Disconnect(L"HandleError");
		break;
	default:
		cout << "Handle Error " << errorCode << endl;
		break;	
	}
}

HANDLE Session::GetHandle()
{
	return reinterpret_cast<HANDLE>(_socket);
}

void Session::Dispatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
	//���� ����� Event�� �Ϸ�Ǿ���!!

	switch (iocpEvent->_eventType)
	{
	case EventType::Connect:
		ProcessConnect();
		break;
	case EventType::Recv:
		ProcessRecv(numOfBytes);
		break;
	case EventType::Send:
		ProcessSend(static_cast<SendEvent*>(iocpEvent), numOfBytes);
		break;
	default:
		break;
	}
}
