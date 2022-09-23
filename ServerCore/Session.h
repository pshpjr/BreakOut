#pragma once
#include "IocpCore.h"
#include "IocpEvent.h"
#include "NetAddress.h"

class Service;

/*Session*/

class Session :public IocpObject
{
	friend class Listener;
	friend class IocpCore;
	friend class Service;
public:
	Session();
	virtual ~Session();

public:

	void			Send(BYTE* buffer, int32 len);
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
	virtual void			Dispatch(IocpEvent* iocpEvent, int32 numOfBytes) override;

private:
							/*���� ����*/

	void					RegisterConnect();
	void					RegisterRecv();
	void					RegisterSend();
	void					RegisterSend(SendEvent* sendEvent);

	void					ProcessConnect();//���� �Ϸ�
	void					ProcessRecv(int32 numOfBytes);
	void					ProcessSend(int32 numOfBytes);
	void					ProcessSend(SendEvent* sendEvent,int32 numOfBytes);

	void					HandleError(int32 errorCode);

protected:
							/*���������� �����ε�*/
							//�����ε� �ϵ� ���� �����Լ��� �� ����(�� ������ �����ϱ�)
	virtual void			OnConnect(){}
	virtual int32			OnRecv(BYTE* buffer, int32 len) { return len; }
	virtual void			OnSend(int32 len){}
	virtual void			OnDisConnected() {}
public:
	//temp. _recvBuffer���� ������ ���⿡ ���� �����Ͱ� �������� ��. 
	BYTE			_recvBuffer[1000] ={};

private:
	weak_ptr<Service>		_service;//���񽺴� �׻� �����״ϱ� null üũ ����?
	SOCKET					_socket = INVALID_SOCKET;
	NetAddress				_netAddress = {};
	Atomic<bool>			_connected = false;

private:
	USE_LOCK;

	/*���� ����*/

	/*�۽� ����*/

private:
	/*������ ȣ���� IO �Լ��� �������̸� ������ ������ ��ü�� ������� �ʵ��� ��*/
/*��� accept �̺�Ʈ�� �ް����� �ִµ� ���� �ٸ� ����*/
	RecvEvent _recvEvent;
};

