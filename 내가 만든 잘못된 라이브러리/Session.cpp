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
		//여기가 자주 딜레이 됨 : 이 세션 접근이 여러곳에서 이뤄지고 있음. 불가능하게 만들었다 생각하는데 어디서 되는지 알아보기
		WRITE_LOCK;
		_sendQueue[QueueNumber].push(sendBuffer);

		if (_sendRegisterd.exchange(true) == false)
			registerSend = true;
	}
	//락을 좀 더 작게 잡을 수 있음.
	//registersend 전체를 락 잡을 필요는 없음
	if(registerSend)
		RegisterSend();
}

bool Session::Connect()
{
	return RegisterConnect();
}

//Q. send 대기중에 클라 접속이 끊어지면 아직 session 객체가 살아 있을 것.
// 이 상황에서 _socket 객체가 사라진다면?
//session은 살아 있겠지만 Iocp 내부에서 send 오류가 나진 않을까?
//Recv는 Recv 받은 후에 Disconnect 하니까 문제 없을 것 같지만

void Session::Disconnect(const WCHAR* cause)
{
	//exchange : 변경해본다. 변경 후 이전에 있던 값을 리턴
	//상태가 false면 걍 패스
	if (_connected.exchange(false) == false)
		return;

	//true일 때 실행

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
	//뭔가 등록한 Event가 완료되었다!!

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

	//아무 주소 아무 포트나
	//안 하면 ConnectEx 에러 남. 
	if (SocketUtils::BindAnyAddress(_socket, 0) == false)
		return false;

	_connectEvent.Init();
	_connectEvent._owner = shared_from_this();

	DWORD numOfBytes = 0;
	//클라에서 호출하면 서버 주소를 받음. 
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

	//reuse 옵션 켜져 있으면 재사용 가능하게 초기화 해서 connect, accept에 사용 가능
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
	//소켓 닫고 세션 release 하면 refcount가 감소. 만약 event가 걸려 있지 않다면 삭제됨
	GetService()->ReleaseSession(GetSessionRef());
}

void Session::RegisterRecv()
{
	P_Event();
	//세션 확인
	if (IsConnected() == false)
		return;

	//recv를 위한 overlapped 초기화 및 등록, recv 호출

	//recvEvent의 주인이 있는 한(이 세션인 한) 이 세션은 삭제되지 않는다.
	_recvEvent.Init();
	_recvEvent._owner = shared_from_this();

	//이벤트 내부에 넣어도 되고 스택에서 만들어도 된다. 사실 이 객체는 값 넘겨줄 때 쓰고 _recvBuf 소멸만 안 되면 상관 xx
	WSABUF wsaBuf;
	wsaBuf.buf = reinterpret_cast<char*>(_recvBuffer.WritePos());
	wsaBuf.len = _recvBuffer.FreeSize();// 이만큼 쓰는 게 아니라 최대로 넣을 수 있는 데이터라 상관x

	DWORD numOfBytes = 0;
	DWORD flags = 0;

	ASSERT_CRASH(_socket != INVALID_SOCKET);
	if (SOCKET_ERROR == WSARecv(_socket, &wsaBuf, 1, &numOfBytes, &flags, &_recvEvent, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if(errorCode != WSA_IO_PENDING)
		{
			HandleError(errorCode);
			//초기화 안 해주면 Iocp에 완료 통지가 뜨지 않을거라 계속 대기중일 것
			//이 세션 삭제해야 함
			_recvEvent._owner = nullptr;

		}
	}
	
}

void Session:: RegisterSend()
{
	//send를 단계별로 이해할 수 있게 임시 코드가 많음.
//그래도 문제점을 쉽게 이해할 수 있다.
	P_Event();

	if (IsConnected() == false)
		return;

	_sendEvent.Init();
	_sendEvent._owner = shared_from_this();

	//나중에 외부에서 락 안잡고 호출할수도 있으니 안에서 락 잡음
	
	
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
		//TODO: 너무 많으면 break;
		data->pop();
		_sendEvent.sendBuffers.push_back(sendBuffer);
	}
	Vector<WSABUF> wsabufs;
	//scatter gather : 흩어진 데이터를 한 번에 보낸다.
	
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

	//세션 등록
	GetService()->AddSession(GetSessionRef());

	//컨텐츠에서 오버로딩
	OnConnected();

	//수신 등록

	RegisterRecv();
}

void Session::ProcessRecv(int32 numOfBytes)
{
	//어짜피 event를 나만 쓸건데 owner를 안 날려도 되지 않을까?
	//생명주기를 명확하게 관리하기 위함. 만약 생성자에서 만들었다고 하면
	//owner를 언제 날려도 되는지 애매하다.
	//wsaRecv를 호출한 후에는 날리면 안 됨.
	//그래서 명확하게 하기 위해 등록할 때 늘리고 실패, 완료시 줄이는 형태로
	//누락시 레퍼런스 카운팅이 이상해짐. 

	_recvEvent._owner = nullptr;//recv 받았으니까 밀어도 됨. 지금은 recvEvent만 멤버로 가지고 있음. 나중에 send도 추가할 듯
	//받는 건 한군데서 계속 받아도 되지만 보내는건 여러 번 보낼 수 있을텐데
	//지금 구조로는 애매할지도

	if(numOfBytes == 0)
	{
		Disconnect(L"Recv 0");
		_connected.store(false);
		return;
	}
	//읽은거 처리 후
	if(_recvBuffer.OnWrite(numOfBytes) == false)
	{
		Disconnect(L"OnWrite Overflow");
		return;
	}

	int32 dataSize = _recvBuffer.DataSize();
	int32 processLen = OnRecv(_recvBuffer.ReadPos(), dataSize); // 컨텐츠 코드에서 재정의
	if (processLen < 0 || dataSize < processLen || _recvBuffer.OnRead(processLen) == false)
	{
		Disconnect(L"OnRead Overflow");
		return;
	}

	// 커서 정리
	_recvBuffer.Clean();

	// 수신 등록
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


	//resend에서 문제 발생

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

//데이터 받았을 때 호출하는데, 데이터 크기 어떻게 할지는 알아서
//헤더 + 데이터를 데이터 사이즈로 하자.

int32 PacketSession::OnRecv(BYTE* buffer, int32 len)
{
	int32 processLen = 0;
	while (true)
	{
		int32 dataSize = len - processLen;
		//4바이트는 들고 와서 헤더는 볼 수 있는가?
		if (dataSize < sizeof(PacketHeader))
			break;
		PacketHeader header = *reinterpret_cast<PacketHeader*>(&buffer[processLen]);
		if (dataSize < header.size)
			break;

		//패킷 전부 옴

		OnRecvPacket(&buffer[processLen], header.size);

		processLen += header.size;
	}
	return processLen;
}


