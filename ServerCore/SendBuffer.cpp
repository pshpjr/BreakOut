#include "pch.h"
#include "SendBuffer.h"

SendBuffer::SendBuffer(int32 BufferSize)
{
	_buffer.resize(BufferSize);
}

SendBuffer::~SendBuffer()
{
}

void SendBuffer::CopyData(void* data, int32 len)
{
	ASSERT_CRASH(Capacity() >= len);

	::memcpy(_buffer.data(), data, len);
	_writeSize = len;
}
