#pragma once

#define OUT

/*---------------
	  Lock
---------------*/

#define USE_MANY_LOCKS(count)	Lock _locks[count];
#define USE_LOCK				USE_MANY_LOCKS(1)
#define	READ_LOCK_IDX(idx)		ReadLockGuard readLockGuard_##idx(_locks[idx], typeid(this).name());
#define READ_LOCK				READ_LOCK_IDX(0)
#define	WRITE_LOCK_IDX(idx)		WriteLockGuard writeLockGuard_##idx(_locks[idx], typeid(this).name());
#define WRITE_LOCK				WRITE_LOCK_IDX(0)

/*---------------
	  Crash
---------------*/

#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}

//expr이 거짓이면 실행

#define ASSERT_CRASH(expr,cause)	\
{									\
	if (!(expr))					\
	{								\
		CRASH(cause);				\
		__analysis_assume(expr);	\
	}								\
}

/*---------------
	  Profile
---------------*/

//#define USE_PROFILER

#ifdef USE_PROFILER

#define P_START OPTICK_FRAME("MainThread");
#define P_THREAD(NAME) OPTICK_THREAD(##NAME);
#define P_Event(NAME) OPTICK_EVENT(##NAME);
#define P_TEST_START int32 tick = psh::GetTickCount();
#define P_TEST_END(time,string) if (psh::GetTickCount() - tick > (time)) cout << (string) << endl;

#else
#define P_START 
#define P_THREAD(NAME) 
#define P_Event(NAME)
#define P_TEST_START 
#define P_TEST_END
#endif


