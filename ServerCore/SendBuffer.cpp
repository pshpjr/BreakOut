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

//ū ���ۿ��� �ʿ��� ��ŭ ���� �Լ�
//�� ���� �� �ƴϰ� �ϴ� ������ �� �� close ȣ���ϸ�
//�� �� ���� ������ ��ȯ�Ѵ�.
//�̷��� ũ�Ⱑ �����̿��� �� �°� ���� �� ����
SendBufferRef SendBufferManager::Open(uint32 size)
{
	//tls�� ����ؼ� ���� �ִ��� �� ��� �������
	//�� �����庰�� ûũ�� �־ open �� ��

	if (LSendBufferChunk == nullptr) {
		LSendBufferChunk = Pop(); //���⼱ Lock ����. ûũ Ǯ���� ������ ������ ��.
		LSendBufferChunk->Reset();
	}
	ASSERT_CRASH(LSendBufferChunk->IsOpen() == false);

	//�� ������ ������ ���ɷ� ��ü
	//�ݳ��� ���� �־ �����ϰ� ��� ���������� �ֱ⸸ ��.
	if(LSendBufferChunk->FreeSize() < size)
	{
		LSendBufferChunk = Pop();
		LSendBufferChunk->Reset();
	}

	cout << "free " << LSendBufferChunk->FreeSize() << endl;

	return LSendBufferChunk->Open(size);
}


//���� ûũ�� �� ������ �ٽ� �ݳ�
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

	//MakeShared �� ���� ������ ���۷����� 0�̶� �����ϸ� �� �Ǳ� ����
	//�ɹ� �Լ��� �Լ� ���ڷ� ������ �� ����. static�� ������.
	//shared_ptr�� �� ��° ���ڴ� �Լ��� �ּҷ�, ���۷��� ī��Ʈ�� 0�� �� �� ȣ���� �Լ���.
	//MakeShared������ xdelete�� �Ǿ� ����
	//�츮�� �� ���� PushGlobal�� �ٽ� ���Ϳ� ����
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
