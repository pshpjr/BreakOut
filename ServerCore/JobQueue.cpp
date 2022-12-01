#include "pch.h"
#include "JobQueue.h"
#include "GlobalQueue.h"

/*--------------
	JobQueue
---------------*/

void JobQueue::Push(JobRef job, bool pushOnly)
{

	const int32 prevCount = _jobCount.fetch_add(1);
	_jobs.Push(job); // WRITE_LOCK

	// ó�� Job ���� �����尡 ����
	if (prevCount == 0)
	{
		// �������� �ƴϸ� ����
		if (LCurrentJobQueue == nullptr && pushOnly == false)
		{

			Execute();
		}
		else
		{
			// �������̸� ���� ť�� �÷��� ���� �����ϰ�
			GGlobalQueue->Push(shared_from_this());
		}
	}
}

void JobQueue::Execute()
{
	LCurrentJobQueue = this;

	while (true)
	{
		Vector<JobRef> jobs;
		
		_jobs.PopAll(OUT jobs);
		
		//�ش� ��ť�� �ִ� �۾��� ����


		const int32 jobCount = static_cast<int32>(jobs.size());
		for(auto& job : jobs)
		{
			job->Execute();
		}

		// �ϰ� ������ ����
		if (_jobCount.fetch_sub(jobCount) == jobCount)
		{
			LCurrentJobQueue = nullptr;
			return;
		}
		

		const uint64 now = psh::GetTickCount();
		if (now >= LEndTickCount)
		{
			
			LCurrentJobQueue = nullptr;
			// ���� ���߿� �ϵ���
			GGlobalQueue->Push(shared_from_this());
			break;
		}			
	}
}
