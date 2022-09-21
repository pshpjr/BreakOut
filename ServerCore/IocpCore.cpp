#include "pch.h"
#include "IocpCore.h"
#include "IocpEvent.h"


//tmp

IocpCore GIocpCore;


IocpCore::IocpCore()
{
	_iocpHanle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	ASSERT_CRASH(_iocpHanle != INVALID_HANDLE_VALUE);
}

IocpCore::~IocpCore()
{
	CloseHandle(_iocpHanle);
}

//IocpHandle에 새 일감 등록
bool IocpCore::Register(IocpObjectRef iocpObject)
{
	return ::CreateIoCompletionPort(iocpObject->GetHandle(), _iocpHanle,
		0, 0);
	//iocompletionport에 이것저것 다 넣을 수 있음. 세션만 넣는 게 아니라 일감이나 네트워크 아닌 것도 넣어짐
	//'일감'으로 통칭
}

//worker 스레드에서 반복적으로 실행해 일감 확인

bool IocpCore::Dispatch(uint32 timeoutMs)
{
	DWORD numOfBytes = 0;
	ULONG_PTR key = 0;

	//IocpObject, IocpEvent 두 객체가 살아있어야 함. 삭제하면 오염된 메모리를 건드림
	//
	//key를 사용하지 않고, IocpEvent가 호출한곳의 SharedPtr을 가지고 있게 함. 
	IocpEvent* iocpEvent = nullptr;

	if(::GetQueuedCompletionStatus(_iocpHanle, OUT & numOfBytes, OUT &key,OUT reinterpret_cast<LPOVERLAPPED*>(&iocpEvent), timeoutMs))
	{
		IocpObjectRef iocpObject = iocpEvent->_owner;
		iocpObject->Dispatch(iocpEvent, numOfBytes);//여기 dispatch는 콜백 느낌.
	}
	else
	{
		int32 errCode = WSAGetLastError();
		switch (errCode)
		{
		case WAIT_TIMEOUT:
			return false;
		default:
			IocpObjectRef iocpObject = iocpEvent->_owner;
			iocpObject->Dispatch(iocpEvent, numOfBytes);
			break;
		}
		return true;
	}
}
