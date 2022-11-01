#pragma once
#include <functional>

/*---------
	Job
----------*/

using CallbackType = std::function<void()>;

class Job
{
public:
	Job(CallbackType&& callback) : _callback(std::move(callback))
	{
	}

	template<typename T, typename Ret, typename... Args>
	Job(shared_ptr<T> owner, Ret(T::* memFunc)(Args...)/*Ret 타입 리턴, Args...을 인자로 받는 함수 포인터의 이름은 memFunc*/, Args&&... args)
	{
		_callback = [owner, memFunc, args...]()
		{
			//왜 get을 해야 하는가?
			(owner.get()->*memFunc)(args...);
		};
	}

	void Execute()
	{
		_callback();
	}

private:
	CallbackType _callback;
};



