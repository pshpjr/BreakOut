#include "pch.h"
#include "Session.h"
#include "Service.h"
#include "SocketUtils.h"

	/*Session*/
Session::Session():_recvBuffer(BUFFER_SIZE)
{
	_socket = SocketUtils::CreateSocket();
}

Session::~Session()
{
	SocketUtils::Close(_socket);
}



void Session::Send(SendBufferRef sendBuffer)
{
	P_Event();
	if (IsConnected() == false)
		return;
	bool registerSend = false;

	{
		//���Ⱑ ���� ������ �� : �� ���� ������ ���������� �̷����� ����. �Ұ����ϰ� ������� �����ϴµ� ��� �Ǵ��� �˾ƺ���
		WRITE_LOCK;
		_sendQueue[QueueNumber].push(sendBuffer);

		if (_sendRegisterd.exchange(true) == false)
			registerSend = true;
	}
	//���� �� �� �۰� ���� �� ����.
	//registersend ��ü�� �� ���� �ʿ�� ����
	if(registerSend)
		RegisterSend();
}

bool Session::Connect()
{
	return RegisterConnect();
}

//Q. send ����߿� Ŭ�� ������ �������� ���� session ��ü�� ��� ���� ��.
// �� ��Ȳ���� _socket ��ü�� ������ٸ�?
//session�� ��� �ְ����� Iocp ���ο��� send ������ ���� ������?
//Recv�� Recv ���� �Ŀ� Disconnect �ϴϱ� ���� ���� �� ������

void Session::Disconnect(const WCHAR* cause)
{
	//exchange : �����غ���. ���� �� ������ �ִ� ���� ����
	//���°� false�� �� �н�
	if (_connected.exchange(false) == false)
		return;

	//true�� �� ����

	//temp

	wcout << "Disconnect : " << cause << endl;

	RegisterDisconnect();
}

HANDLE Session::GetHandle()
{
	return reinterpret_cast<HANDLE>(_socket);
}
void Session::Dispatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
	P_Event()
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
		ProcessSend(numOfBytes);
		break;
	case EventType::Disconnect:
		ProcessDisconnect();
		break;
	default:
		break;
	}
}

bool Session::RegisterConnect()
{
	if (IsConnected())
		return false;
	if (GetService()->GetServiceType() != ServiceType::Client)
		return false;

	if (SocketUtils::SetReuseAddress(_socket, true) == false)
		return false;

	//�ƹ� �ּ� �ƹ� ��Ʈ��
	//�� �ϸ� ConnectEx ���� ��. 
	if (SocketUtils::BindAnyAddress(_socket, 0) == false)
		return false;

	_connectEvent.Init();
	_connectEvent._owner = shared_from_this();

	DWORD numOfBytes = 0;
	//Ŭ�󿡼� ȣ���ϸ� ���� �ּҸ� ����. 
	SOCKADDR_IN sockAddr = GetService()->GetNetAddress().GetSockAddr();

	if(false == SocketUtils::ConnectEx(_socket,reinterpret_cast<SOCKADDR*>(&sockAddr),sizeof(sockAddr),nullptr,0,&numOfBytes,&_connectEvent))
	{
		int32 errCode = WSAGetLastError();

		if(errCode != WSA_IO_PENDING)
		{
			_connectEvent._owner = nullptr;
			return false;
		}
	}

}

bool Session::RegisterDisconnect()
{
	_disconnectEvent.Init();
	_disconnectEvent._owner = shared_from_this();

	//reuse �ɼ� ���� ������ ���� �����ϰ� �ʱ�ȭ �ؼ� connect, accept�� ��� ����
	if (false == SocketUtils::DisconnectEx(_socket, &_disconnectEvent, TF_REUSE_SOCKET, 0))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			_disconnectEvent._owner = nullptr; // RELEASE_REF
			return false;
		}
	}
	return true;
}

void Session::ProcessDisconnect()
{
	_disconnectEvent._owner = nullptr;

	OnDisconnected();
	//���� �ݰ� ���� release �ϸ� refcount�� ����. ���� event�� �ɷ� ���� �ʴٸ� ������
	GetService()->ReleaseSession(GetSessionRef());
}

void Session::RegisterRecv()
{
	P_Event();
	//���� Ȯ��
	if (IsConnected() == false)
		return;

	//recv�� ���� overlapped �ʱ�ȭ �� ���, recv ȣ��

	//recvEvent�� ������ �ִ� ��(�� ������ ��) �� ������ �������� �ʴ´�.
	_recvEvent.Init();
	_recvEvent._owner = shared_from_this();

	//�̺�Ʈ ���ο� �־ �ǰ� ���ÿ��� ���� �ȴ�. ��� �� ��ü�� �� �Ѱ��� �� ���� _recvBuf �Ҹ길 �� �Ǹ� ��� xx
	WSABUF wsaBuf;
	wsaBuf.buf = reinterpret_cast<char*>(_recvBuffer.WritePos());
	wsaBuf.len = _recvBuffer.FreeSize();// �̸�ŭ ���� �� �ƴ϶� �ִ�� ���� �� �ִ� �����Ͷ� ���x

	DWORD numOfBytes = 0;
	DWORD flags = 0;

	ASSERT_CRASH(_socket != INVALID_SOCKET);
	if (SOCKET_ERROR == WSARecv(_socket, &wsaBuf, 1, &numOfBytes, &flags, &_recvEvent, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if(errorCode != WSA_IO_PENDING)
		{
			HandleError(errorCode);
			//�ʱ�ȭ �� ���ָ� Iocp�� �Ϸ� ������ ���� �����Ŷ� ��� ������� ��
			//�� ���� �����ؾ� ��
			_recvEvent._owner = nullptr;

		}
	}
	
}

void Session:: RegisterSend()
{
	//send�� �ܰ躰�� ������ �� �ְ� �ӽ� �ڵ尡 ����.
//�׷��� �������� ���� ������ �� �ִ�.
	P_Event();

	if (IsConnected() == false)
		return;

	_sendEvent.Init();
	_sendEvent._owner = shared_from_this();

	//���߿� �ܺο��� �� ����� ȣ���Ҽ��� ������ �ȿ��� �� ����
	
	
	int32 writeSize = 0;
	Queue<SendBufferRef>* data;
	{
		WRITE_LOCK;
		data = &_sendQueue[QueueNumber];
		QueueNumber ^= 1;
	}


	while(data->empty() == false)
	{
		SendBufferRef sendBuffer = data->front();

		writeSize += sendBuffer->WriteSize();
		//TODO: �ʹ� ������ break;
		data->pop();
		_sendEvent.sendBuffers.push_back(sendBuffer);
	}
	Vector<WSABUF> wsabufs;
	//scatter gather : ����� �����͸� �� ���� ������.
	
	wsabufs.reserve(_sendEvent.sendBuffers.size());
	for (const SendBufferRef& sendBuffer : _sendEvent.sendBuffers)
	{
		WSABUF wsaBuf;
		wsaBuf.buf = reinterpret_cast<char*>(sendBuffer->Buffer());
		wsaBuf.len = static_cast<LONG>(sendBuffer->WriteSize());
		wsabufs.push_back(wsaBuf);
	}

	DWORD numOfBytes = 0;
	if (SOCKET_ERROR == ::WSASend(_socket, wsabufs.data(), static_cast<DWORD>(wsabufs.size()), OUT & numOfBytes, 0, &_sendEvent, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			HandleError(errorCode);
			_sendEvent._owner = nullptr;
			_sendEvent.sendBuffers.clear();
			_sendRegisterd.store(false);
		}
	}

}


void Session::ProcessConnect()
{
	_connectEvent._owner = nullptr;
	_connected.store(true);

	//���� ���
	GetService()->AddSession(GetSessionRef());

	//���������� �����ε�
	OnConnected();

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
		_connected.store(false);
		return;
	}
	//������ ó�� ��
	if(_recvBuffer.OnWrite(numOfBytes) == false)
	{
		Disconnect(L"OnWrite Overflow");
		return;
	}

	int32 dataSize = _recvBuffer.DataSize();
	int32 processLen = OnRecv(_recvBuffer.ReadPos(), dataSize); // ������ �ڵ忡�� ������
	if (processLen < 0 || dataSize < processLen || _recvBuffer.OnRead(processLen) == false)
	{
		Disconnect(L"OnRead Overflow");
		return;
	}

	// Ŀ�� ����
	_recvBuffer.Clean();

	// ���� ���
	RegisterRecv();
}

void Session::ProcessSend(int32 numOfBytes)
{
	_sendEvent._owner = nullptr;
	_sendEvent.sendBuffers.clear();
	_sendRegisterd.store(false);
	if (numOfBytes == 0)
	{
		Disconnect(L"send 0");
		return;
	}

	OnSend(numOfBytes);


	//resend���� ���� �߻�

	{
		P_Event("SwapSendQueue")
		WRITE_LOCK;
		if (_sendQueue[QueueNumber].empty()) {
			_sendRegisterd.store(false);
			return;
		}
	}
	//{
	//	P_Event("Resend")
	//	RegisterSend();
	//}
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

PacketSession::PacketSession()
{

}

PacketSession::~PacketSession()
{

}

//������ �޾��� �� ȣ���ϴµ�, ������ ũ�� ��� ������ �˾Ƽ�
//��� + �����͸� ������ ������� ����.

int32 PacketSession::OnRecv(BYTE* buffer, int32 len)
{
	int32 processLen = 0;
	while (true)
	{
		int32 dataSize = len - processLen;
		//4����Ʈ�� ��� �ͼ� ����� �� �� �ִ°�?
		if (dataSize < sizeof(PacketHeader))
			break;
		PacketHeader header = *reinterpret_cast<PacketHeader*>(&buffer[processLen]);
		if (dataSize < header.size)
			break;

		//��Ŷ ���� ��

		OnRecvPacket(&buffer[processLen], header.size);

		processLen += header.size;
	}
	return processLen;
}


