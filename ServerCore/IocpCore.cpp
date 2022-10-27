#include "pch.h"
#include "IocpCore.h"
#include "IocpEvent.h"




IocpCore::IocpCore()
{
	_iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	ASSERT_CRASH(_iocpHandle != INVALID_HANDLE_VALUE);
}

IocpCore::~IocpCore()
{
	CloseHandle(_iocpHandle);
}

//IocpHandle�� �� �ϰ� ���
bool IocpCore::Register(IocpObjectRef iocpObject)
{
	return ::CreateIoCompletionPort(iocpObject->GetHandle(), _iocpHandle,
		0, 0);
	//iocompletionport�� �̰����� �� ���� �� ����. ���Ǹ� �ִ� �� �ƴ϶� �ϰ��̳� ��Ʈ��ũ �ƴ� �͵� �־���
	//'�ϰ�'���� ��Ī
}

//worker �����忡�� �ݺ������� ������ �ϰ� Ȯ��

bool IocpCore::Dispatch(uint32 timeoutMs)
{
	DWORD numOfBytes = 0;
	ULONG_PTR key = 0;

	//IocpObject, IocpEvent �� ��ü�� ����־�� ��. �����ϸ� ������ �޸𸮸� �ǵ帲
	//
	//key�� ������� �ʰ�, IocpEvent�� ȣ���Ѱ��� SharedPtr�� ������ �ְ� ��. 
	IocpEvent* iocpEvent = nullptr;

	if(::GetQueuedCompletionStatus(_iocpHandle, OUT & numOfBytes, OUT &key,OUT reinterpret_cast<LPOVERLAPPED*>(&iocpEvent), timeoutMs))
	{
		IocpObjectRef iocpObject = iocpEvent->_owner;
		iocpObject->Dispatch(iocpEvent, numOfBytes);//���� dispatch�� �ݹ� ����.
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
