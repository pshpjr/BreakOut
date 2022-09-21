#pragma once
class Session;

enum class EventType :uint8
{
	Connect,
	Accept,
	Recv,
	Send
};

//이렇게 상속  받으면 0번 주소에 OVERLAPPED 데이터부터 들어가니까
//예전에 OverlappedEx 첫 멤버로 OVERLAPPED 들고 있는 거랑 같은 역할을 함. 
//iocp에 넣어줄 때 어떤 이유로 넣는지 확인하는 역할. 
class IocpEvent : public OVERLAPPED
{
public:
	IocpEvent(EventType type);

	void			Init();


public:
	EventType		_eventType;
	IocpObjectRef	_owner;
};

/*
 * ConnectEvent
 */
class ConnectEvent : public IocpEvent
{
public:
	ConnectEvent() : IocpEvent(EventType::Connect) { }
};


/*
 * AcceptEvent
 */
class AcceptEvent : public IocpEvent
{
public:
	AcceptEvent() : IocpEvent(EventType::Accept) {}

public:
	SessionRef _session = nullptr;
};


/*
 * RecvEvent
 */
class RecvEvent : public IocpEvent
{
public:
	RecvEvent() : IocpEvent(EventType::Recv) { }
};


/*
 * SendEvent
 */
class SendEvent : public IocpEvent
{
public:
	SendEvent() : IocpEvent(EventType::Send) { }
};