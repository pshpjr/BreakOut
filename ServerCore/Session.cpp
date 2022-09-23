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

//Q. send 대기중에 클라 접속이 끊어지면 아직 session 객체가 살아 있을 것.
// 이 상황에서 _socket 객체가 사라진다면?
//session은 살아 있겠지만 Iocp 내부에서 send 오류가 나진 않을까?
//Recv는 Recv 받은 후에 Disconnect 하니까 문제 없을 것 같지만
void Session::Disconnect(const WCHAR* cause)
{
	//exchange : 변경해본다. 기존 값이랑 넣을 값이랑 같으면 false를 리턴
	//상태가 false면 걍 패스
	if (_connected.exchange(false) == false)
		return;

	//true일 때 실행

	//temp

	wcout << "Disconnect : " << cause << endl;

	OnDisConnected();

	//소켓 닫고 세션 release 하면 refcount가 감소. 만약 event가 걸려 있지 않다면 삭제됨
	SocketUtils::Close(_socket);
	GetService()->ReleaseSession(GetSessionRef());

	
}

void Session::RegisterConnect()
{


}

void Session::RegisterRecv()
{
	//세션 확인
	if (IsConnected() == false)
		return;

	//recv를 위한 overlapped 초기화 및 등록, recv 호출

	//recvEvent의 주인이 있는 한(이 세션인 한) 이 세션은 삭제되지 않는다.
	_recvEvent.Init();
	_recvEvent._owner = shared_from_this();

	//이벤트 내부에 넣어도 되고 스택에서 만들어도 된다. 사실 이 객체는 값 넘겨줄 때 쓰고 _recvBuf 소멸만 안 되면 상관 xx
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
			//에러 처리후
			HandleError(errorCode);

			//초기화 안 해주면 Iocp에 완료 통지가 뜨지 않을거라 계속 대기중일 것
			//이 세션 삭제해야 함
			_recvEvent._owner = nullptr;

		}
	}
	
}

void Session::RegisterSend()
{
}

//sendEvent를 맴버로 가지고 있지 않으니까 일단 넘겨주는 버전 임시로 만들어 사용
void Session::RegisterSend(SendEvent* sendEvent)
{
	//send를 단계별로 이해할 수 있게 임시 코드가 많음.
	//그래도 문제점을 쉽게 이해할 수 있다.

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

	//세션 등록
	GetService()->AddSession(GetSessionRef());

	//컨텐츠에서 오버로딩
	OnConnect();

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
		return;
	}

	OnRecv(_recvBuffer,numOfBytes);

	//수신 등록. 데이터 뺀 후 다시 받는다고 해야 함. 
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
		ProcessSend(static_cast<SendEvent*>(iocpEvent), numOfBytes);
		break;
	default:
		break;
	}
}
