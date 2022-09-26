#pragma once
#include "IocpCore.h"
#include "IocpEvent.h"
#include "NetAddress.h"
#include "RecvBuffer.h"
class Service;

/*Session*/

class Session :public IocpObject
{
	friend class Listener;
	friend class IocpCore;
	friend class Service;

	enum { BUFFER_SIZE = 0x10000, };// 64kb;


public:
	Session();
	virtual ~Session();

public:

	void			Send(SendBufferRef sendBuffer);
	bool			Connect();
	void			Disconnect(const WCHAR* cause/*왜 끊었는지*/);//해당 세션 종료(밴, 상대방 종료 등등)


	shared_ptr<Service> GetService() { return _service.lock(); }
	void			SetService(shared_ptr<Service> service) { _service = service; }

public:
	/*정보 관련*/
	void			SetNetAddress(NetAddress address) { _netAddress = address; }
	NetAddress		GetAddress() { return _netAddress; }
	SOCKET			GetSocket() { return _socket; }
	bool			IsConnected() { return _connected; }
	SessionRef		GetSessionRef() { return static_pointer_cast<Session>(shared_from_this()); }



private:
	/*인터페이스 구현*/
	virtual HANDLE			GetHandle() override;
	virtual void			Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) override;

private:
							/*전송 관련*/

	bool					RegisterConnect();
	bool					RegisterDisconnect();
	void					RegisterRecv();
	void					RegisterSend();

	void					ProcessConnect();//연결 완료
	void					ProcessDisconnect();
	void					ProcessRecv(int32 numOfBytes);
	void					ProcessSend(int32 numOfBytes);

	void					HandleError(int32 errorCode);

protected:
							/*컨텐츠에서 오버로딩*/
							//오버로딩 하되 완전 가상함수론 안 만듬(안 쓸수도 있으니까)
	virtual void			OnConnected(){}
	virtual int32			OnRecv(BYTE* buffer, int32 len) { return len; }
	virtual void			OnSend(int32 len){}
	virtual void			OnDisconnected() {}

private:
	weak_ptr<Service>		_service;//서비스는 항상 있을테니까 null 체크 딱히?
	SOCKET					_socket = INVALID_SOCKET;
	NetAddress				_netAddress = {};
	Atomic<bool>			_connected = false;

private:
	USE_LOCK;

	/*수신 관련*/
	RecvBuffer				_recvBuffer;
	/*송신 관련*/
	Queue<SendBufferRef>	_sendQueue;
	Atomic<bool>			_sendRegisterd = false;

private:
	/*세션이 호출한 IO 함수가 진행중이면 세션을 참조해 객체가 사라지지 않도록 함*/
/*얘랑 accept 이벤트랑 햇갈리고 있는데 둘은 다른 거임*/
	ConnectEvent			_connectEvent;
	DisconnectEvent			_disconnectEvent;
	RecvEvent				_recvEvent;
	SendEvent				_sendEvent;
};

/*PacketSession*/
//받는 쪽이랑 관련이 있음. 우리가 Recv 끝날 때 전부 다 받지 않을 수 있음.
//전체 패킷을 다 보냈는지 알려줄 수 있는 프로토콜을 정해야 함.
//어떻게 데이터 끝을 알리느나?
//1. 특수문자를 쓴다면? 데이터가 겹칠 수 있음.
//2. 정석은 패킷 헤더. string 같은 가변 데이터 위해 size를 사용

struct PacketHeader
{
	uint16 size;//패킷 크기
	uint16 id;//데이터 종류
};

//컨텐츠에선 패킷 세션 상속받아서 
class PacketSession : public Session
{
public:
	PacketSession();
	~PacketSession();

	PacketSessionRef GetPacketSessionRef() { return static_pointer_cast<PacketSession>(shared_from_this()); }

protected:
	int32 OnRecv(BYTE* buffer, int32 len) sealed;
	virtual int32 OnRecvPacket(BYTE* buffer, int32 len) abstract;

};