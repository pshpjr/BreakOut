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

//IocpHandle�� �� �ϰ� ���
bool IocpCore::Register(IocpObject* iocpObject)
{
	return ::CreateIoCompletionPort(iocpObject->GetHandle(), _iocpHanle,
		reinterpret_cast<ULONG_PTR>(iocpObject), 0);
	//iocompletionport�� �̰����� �� ���� �� ����. ���Ǹ� �ִ� �� �ƴ϶� �ϰ��̳� ��Ʈ��ũ �ƴ� �͵� �־���
	//'�ϰ�'���� ��Ī
}

//worker �����忡�� �ݺ������� ������ �ϰ� Ȯ��

bool IocpCore::Dispatch(uint32 timeoutMs)
{
	DWORD numOfBytes = 0;

	//�� �� ��ü�� ����־�� ��. 
	IocpObject* iocpObject = nullptr;
	IocpEvent* iocpEvent = nullptr;

	if(::GetQueuedCompletionStatus(_iocpHanle, OUT & numOfBytes, OUT reinterpret_cast<PULONG_PTR>(&iocpObject),OUT reinterpret_cast<LPOVERLAPPED*>(&iocpEvent), timeoutMs))
	{
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
			iocpObject->Dispatch(iocpEvent, numOfBytes);
			break;
		}
		return true;
	}
}
