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
	void			Disconnect(const WCHAR* cause/*�� ��������*/);//�ش� ���� ����(��, ���� ���� ���)


	shared_ptr<Service> GetService() { return _service.lock(); }
	void			SetService(shared_ptr<Service> service) { _service = service; }

public:
	/*���� ����*/
	void			SetNetAddress(NetAddress address) { _netAddress = address; }
	NetAddress		GetAddress() { return _netAddress; }
	SOCKET			GetSocket() { return _socket; }
	bool			IsConnected() { return _connected; }
	SessionRef		GetSessionRef() { return static_pointer_cast<Session>(shared_from_this()); }



private:
	/*�������̽� ����*/
	virtual HANDLE			GetHandle() override;
	virtual void			Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) override;

private:
							/*���� ����*/

	bool					RegisterConnect();
	bool					RegisterDisconnect();
	void					RegisterRecv();
	void					RegisterSend();

	void					ProcessConnect();//���� �Ϸ�
	void					ProcessDisconnect();
	void					ProcessRecv(int32 numOfBytes);
	void					ProcessSend(int32 numOfBytes);

	void					HandleError(int32 errorCode);

protected:
							/*���������� �����ε�*/
							//�����ε� �ϵ� ���� �����Լ��� �� ����(�� ������ �����ϱ�)
	virtual void			OnConnected(){}
	virtual int32			OnRecv(BYTE* buffer, int32 len) { return len; }
	virtual void			OnSend(int32 len){}
	virtual void			OnDisconnected() {}

private:
	weak_ptr<Service>		_service;//���񽺴� �׻� �����״ϱ� null üũ ����?
	SOCKET					_socket = INVALID_SOCKET;
	NetAddress				_netAddress = {};
	Atomic<bool>			_connected = false;

private:
	USE_LOCK;

	/*���� ����*/
	RecvBuffer				_recvBuffer;
	/*�۽� ����*/
	Queue<SendBufferRef>	_sendQueue;
	Atomic<bool>			_sendRegisterd = false;

private:
	/*������ ȣ���� IO �Լ��� �������̸� ������ ������ ��ü�� ������� �ʵ��� ��*/
/*��� accept �̺�Ʈ�� �ް����� �ִµ� ���� �ٸ� ����*/
	ConnectEvent			_connectEvent;
	DisconnectEvent			_disconnectEvent;
	RecvEvent				_recvEvent;
	SendEvent				_sendEvent;
};

/*PacketSession*/
//�޴� ���̶� ������ ����. �츮�� Recv ���� �� ���� �� ���� ���� �� ����.
//��ü ��Ŷ�� �� ���´��� �˷��� �� �ִ� ���������� ���ؾ� ��.
//��� ������ ���� �˸�����?
//1. Ư�����ڸ� ���ٸ�? �����Ͱ� ��ĥ �� ����.
//2. ������ ��Ŷ ���. string ���� ���� ������ ���� size�� ���

struct PacketHeader
{
	uint16 size;//��Ŷ ũ��
	uint16 id;//������ ����
};

//���������� ��Ŷ ���� ��ӹ޾Ƽ� 
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