#pragma once
#include "NetAddress.h"
#include "IocpCore.h"
#include "IocpEvent.h"

/*
 * Listener
 */

class AcceptEvent;
class ServerService;

class AcceptEvent;
//�ȳ��� ����
class Listener :public IocpObject
{
public:
	Listener() = default;
	~Listener();

public:
/*�ܺο��� ���*/
	bool StartAccept(ServerServiceRef service);
	void CloseSocket();

public:
	//�������̽� ����
	HANDLE GetHandle() override;
	void Dispatch(IocpEvent* iocpEvent, int32 numOfBytes) override;

private:
	/*���� ���� �ڵ�*/
	void RegisterAccept(AcceptEvent* acceptEvent);
	void ProcessAccept(AcceptEvent* acceptEvent);//register �Ѱ� �Ϸ�Ǿ ������ �� ���� ��

protected:
	SOCKET _socket = INVALID_SOCKET;//��������
	vector<AcceptEvent*> _acceptEvents;
	//��ȣ ���� ����
	ServerServiceRef _service;
};

