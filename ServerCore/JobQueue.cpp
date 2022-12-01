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

	// 처음 Job 넣은 스레드가 실행
	if (prevCount == 0)
	{
		// 실행중이 아니면 실행
		if (LCurrentJobQueue == nullptr && pushOnly == false)
		{

			Execute();
		}
		else
		{
			// 실행중이면 전역 큐에 올려서 남이 실행하게
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
		
		//해당 잡큐에 있는 작업들 실행


		const int32 jobCount = static_cast<int32>(jobs.size());
		for(auto& job : jobs)
		{
			job->Execute();
		}

		// 일감 없으면 종료
		if (_jobCount.fetch_sub(jobCount) == jobCount)
		{
			LCurrentJobQueue = nullptr;
			return;
		}
		

		const uint64 now = psh::GetTickCount();
		if (now >= LEndTickCount)
		{
			
			LCurrentJobQueue = nullptr;
			// 남이 나중에 하도록
			GGlobalQueue->Push(shared_from_this());
			break;
		}			
	}
}
