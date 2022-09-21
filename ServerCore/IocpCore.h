#pragma once

/*
 * IocpObject
 */

//�ڱ� �ڽſ� ���� weakptr�� ������ ����. 
class IocpObject : public enable_shared_from_this<IocpObject>//Iocp�� ���� ��ü���� �̰� ��ӹ���. 
{
public:
	virtual HANDLE GetHandle() abstract;
	virtual void Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) abstract;
};

class IocpCore
{
public:
	IocpCore();
	~IocpCore();

	HANDLE GetHandle() { return _iocpHanle; }

	bool Register(IocpObjectRef iocpObject);
	bool Dispatch(uint32 timeoutMs = INFINITE);//������ �ϰ��� ������ ���� ��������� ����. 

private:
	HANDLE _iocpHanle;
};
