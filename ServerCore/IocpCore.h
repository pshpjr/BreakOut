#pragma once

/*
 * IocpObject
 */
class IocpObject //Iocp에 넣을 객체들은 이걸 상속받음. 
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

	bool Register(class IocpObject* iocpObject);
	bool Dispatch(uint32 timeoutMs = INFINITE);//실제로 일감을 가지고 오는 스레드들을 실행. 

private:
	HANDLE _iocpHanle;
};

extern IocpCore GIocpCore;