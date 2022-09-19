#pragma once
#include "NetAddress.h"
#include "IocpCore.h"
#include "IocpEvent.h"

/*
 * Listener
 */

class AcceptEvent;
//안내원 역할
class Listener :public IocpObject
{
public:
	Listener() = default;
	~Listener();

public:
/*외부에서 사용*/
	bool StartAccept(NetAddress netAddress);
	void CloseSocket();

public:
	//인터페이스 구현
	HANDLE GetHandle() override;
	void Dispatch(IocpEvent* iocpEvent, int32 numOfBytes) override;

private:
	/*수신 관련 코드*/
	void RegisterAccept(AcceptEvent* acceptEvent);
	void ProcessAccept(AcceptEvent* acceptEvent);//register 한게 완료되어서 진행할 수 있을 때

protected:
	SOCKET _socket = INVALID_SOCKET; //리스너 소켓
	vector<AcceptEvent*> _acceptEvents;
};

