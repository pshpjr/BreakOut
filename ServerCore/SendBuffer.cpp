#include "pch.h"
#include "SendBuffer.h"

SendBuffer::SendBuffer(SendBufferChunkRef owner, BYTE* buffer, uint32 allocSize)
	:_owner(owner),_buffer(buffer),_allocSize(allocSize)
{

}

SendBuffer::~SendBuffer()
{
}

void SendBuffer::Close(uint32 writeSize)
{
	ASSERT_CRASH(_allocSize >= writeSize);

	_writeSize = writeSize;
	_owner->Close(writeSize);
}

SendBufferChunk::SendBufferChunk()
{
}

SendBufferChunk::~SendBufferChunk()
{
}

void SendBufferChunk::Reset()
{
	_open = false;
	_usedSize = 0;

}

SendBufferRef SendBufferChunk::Open(uint32 allocSize)
{
	ASSERT_CRASH(allocSize <= SEND_BUFFER_CHUNK_SIZE);
	ASSERT_CRASH(_open == false);

	if (allocSize > FreeSize())
		return nullptr;

	_open = true;
	return ObjectPool<SendBuffer>::MakeShared(shared_from_this(),Buffer(),allocSize);

}

void SendBufferChunk::Close(uint32 writeSize)
{
	ASSERT_CRASH(_open == true);
	_open = false;
	_usedSize += writeSize;
}

//큰 버퍼에서 필요한 만큼 뜯어가는 함수
//다 쓰는 건 아니고 일단 가지고 간 후 close 호출하면
//그 때 쓰고 남은건 반환한다.
//이러면 크기가 동적이여도 딱 맞게 만들 수 있음
SendBufferRef SendBufferManager::Open(uint32 size)
{
	//tls를 사용해서 락을 최대한 안 잡게 만들거임
	//각 스레드별로 청크가 있어서 open 할 때

	if (LSendBufferChunk == nullptr) {
		LSendBufferChunk = Pop(); //여기선 Lock 있음. 청크 풀에서 가지고 오려고 함.
		LSendBufferChunk->Reset();
	}
	ASSERT_CRASH(LSendBufferChunk->IsOpen() == false);

	//다 썼으면 버리고 새걸로 교체
	//반납한 공간 있어도 무시하고 계속 오른쪽으로 넣기만 함.
	if(LSendBufferChunk->FreeSize() < size)
	{
		LSendBufferChunk = Pop();
		LSendBufferChunk->Reset();
	}

	cout << "free " << LSendBufferChunk->FreeSize() << endl;

	return LSendBufferChunk->Open(size);
}


//버퍼 청크를 다 썼으면 다시 반납
SendBufferChunkRef SendBufferManager::Pop()
{
	cout << "PopGlobal" << endl;
	{
		WRITE_LOCK;
		if(_sendBufferChunks.empty()==false)
		{
			SendBufferChunkRef sendBufferChunk = _sendBufferChunks.back();
			_sendBufferChunks.pop_back();
			return sendBufferChunk;
		}

	}

	//MakeShared 안 쓰는 이유는 레퍼런스가 0이라도 삭제하면 안 되기 떄문
	//맴버 함수는 함수 인자로 전달할 수 없다. static만 가능함.
	//shared_ptr의 두 번째 인자는 함수의 주소로, 레퍼런스 카운트가 0이 될 때 호출할 함수다.
	//MakeShared에서는 xdelete로 되어 있음
	//우리는 다 쓰면 PushGlobal로 다시 벡터에 삽입
	return SendBufferChunkRef(xnew<SendBufferChunk>(), PushGlobal);
}

void SendBufferManager::Push(SendBufferChunkRef buffer)
{
	WRITE_LOCK;
	_sendBufferChunks.push_back(buffer);
}

void SendBufferManager::PushGlobal(SendBufferChunk* buffer)
{
	cout << "PushGlobal" << endl;

	GSendBufferManager->Push(SendBufferChunkRef(buffer, PushGlobal));
}
