#pragma once
#include "pch.h"
#include "Job.h"
#include "LockQueue.h"
#include "JobTimer.h"

/*--------------
	JobQueue
---------------*/

class JobQueue : public enable_shared_from_this<JobQueue>
{
public:
	void DoAsync(CallbackType&& callback)
	{
		Push(ObjectPool<Job>::MakeShared(std::move(callback)));
	}

	template<typename T, typename Ret, typename... Args>
	void DoAsync(Ret(T::* memFunc)(Args...), Args... args)
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		Push(ObjectPool<Job>::MakeShared(owner, memFunc, std::forward<Args>(args)...));
	}

	template<typename T, typename Ret>
	void DoAsync(Ret(T::* memFunc)())
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		Push(ObjectPool<Job>::MakeShared(owner, memFunc));
	}

	template<typename T, typename Ret, typename Arg1>
	void DoAsync(Ret(T::* memFunc)(Arg1), Arg1 arg1)
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		Push(ObjectPool<Job>::MakeShared(owner, memFunc, std::forward<Arg1>(arg1)));
	}

	template<typename T, typename Ret, typename Arg1, typename Arg2>
	void DoAsync(Ret(T::* memFunc)(Arg1, Arg2), Arg1 arg1, Arg2 arg2)
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		Push(ObjectPool<Job>::MakeShared(owner, memFunc, std::forward<Arg1>(arg1),std::forward<Arg2>(arg2)));
	}

	void DoTimer(uint64 tickAfter, CallbackType&& callback)
	{
		JobRef job = ObjectPool<Job>::MakeShared(std::move(callback));
		GJobTimer->Reserve(tickAfter, shared_from_this(), job);
	}

	template<typename T, typename Ret, typename... Args>
	void DoTimer(uint64 tickAfter, Ret(T::* memFunc)(Args...), Args... args)
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		JobRef job = ObjectPool<Job>::MakeShared(owner, memFunc, std::forward<Args>(args)...);
		GJobTimer->Reserve(tickAfter, shared_from_this(), job);
	}

	template<typename T, typename Ret>
	void DoTimer(uint64 tickAfter, Ret(T::* memFunc)())
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		JobRef job = ObjectPool<Job>::MakeShared(owner, memFunc);
		GJobTimer->Reserve(tickAfter, shared_from_this(), job);
	}

	template<typename T, typename Ret, typename Arg1>
	void DoTimer(uint64 tickAfter, Ret(T::* memFunc)(Arg1), Arg1 arg1)
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		JobRef job = ObjectPool<Job>::MakeShared(owner, memFunc, std::forward<Arg1>(arg1));
		GJobTimer->Reserve(tickAfter, shared_from_this(), job);
	}

	template<typename T, typename Ret, typename Arg1, typename Arg2>
	void DoTimer(uint64 tickAfter, Ret(T::* memFunc)(Arg1, Arg2), Arg1 arg1, Arg2 arg2)
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		JobRef job = ObjectPool<Job>::MakeShared(owner, memFunc, std::forward<Arg1>(arg1), std::forward<Arg2>(arg2));
		GJobTimer->Reserve(tickAfter, shared_from_this(), job);
	}

	template<typename T, typename Ret, typename Arg1, typename Arg2, typename Arg3>
	void DoTimer(uint64 tickAfter, Ret(T::* memFunc)(Arg1, Arg2, Arg3), Arg1 arg1, Arg2 arg2, Arg3 arg3)
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		JobRef job = ObjectPool<Job>::MakeShared(owner, memFunc, std::forward<Arg1>(arg1), std::forward<Arg2>(arg2), std::forward<Arg3>(arg3));
		GJobTimer->Reserve(tickAfter, shared_from_this(), job);
	}

	void					ClearJobs() { _jobs.Clear(); }

public:
	void					Push(JobRef job, bool pushOnly = false);
	void					Execute();

protected:
	LockQueue<JobRef>		_jobs;
	Atomic<int32>			_jobCount = 0;
};


