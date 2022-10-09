#pragma once
#include "pch.h"

#include "Service.h"

class DummyService : public ClientService
{
public:
	DummyService(const NetAddress& targetAddress, const IocpCoreRef& core, const SessionFactory& factory,
		int32 maxSessionCount)
		: ClientService(targetAddress, core, factory, maxSessionCount)
	{
	}


	Set<SessionRef>& getSessions() { return _sessions; }
};
