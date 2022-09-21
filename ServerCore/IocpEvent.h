#pragma once
class Session;

enum class EventType :uint8
{
	Connect,
	Accept,
	Recv,
	Send
};

//�̷��� ���  ������ 0�� �ּҿ� OVERLAPPED �����ͺ��� ���ϱ�
//������ OverlappedEx ù ����� OVERLAPPED ��� �ִ� �Ŷ� ���� ������ ��. 
//iocp�� �־��� �� � ������ �ִ��� Ȯ���ϴ� ����. 
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