#pragma once
#include "NetAddress.h"
#include "IocpCore.h"
#include "Listener.h"
#include <functional>

enum class ServiceType : uint8
{
	Server,
	Client
};

/**
 * Service
 */

using SessionFactory = function<SessionRef(void)>;


class Service : public enable_shared_from_this<Service>
{
public:
	Service(ServiceType type/*서버 클라 여부*/, NetAddress address/*연결할 주소*/, IocpCoreRef core, SessionFactory factory, int32 maxSessionCount = 1);
	virtual ~Service();

	virtual bool		Start() abstract;
	bool				CanStart() { return _sessionFactory != nullptr; }

	virtual void		CloseService();
	void				SetSessionFactory(SessionFactory func) { _sessionFactory = func; };

	SessionRef			CreateSession();//세션 생성, IocpCore에 등록
	void				AddSession(SessionRef session);//있는 세션을 추가
	void				ReleaseSession(SessionRef session);
	int32				GetCurrentSessionCount() { return _sessionCount; }//lock 잡진 않아서 부정확. 근데 부정확해도 충분
	int32				GetMaxSessionCount() { return _maxSessionCount; }

public:
	ServiceType			GetServiceType() { return _type; }
	NetAddress			GetNetAddress() { return _netAddress; }
	IocpCoreRef&		GetIocpCore() { return _iocpCore; }//자주 쓸 함수라 레퍼런스 카운트 늘리기보단 참조로 넘김. 잠시만 써야 함

protected:
	USE_LOCK;

	ServiceType				_type;
	NetAddress				_netAddress = {};
	IocpCoreRef				_iocpCore;

	Set<SessionRef>			_sessions;
	int32					_sessionCount = 0;
	int32					_maxSessionCount = 0;
	SessionFactory			_sessionFactory;
};

/**
 * Client Service
 */
class ClientService : public Service // 클라이언트에서 실행
{
public:
	ClientService(NetAddress targetAddress, IocpCoreRef core, SessionFactory factory, int32 maxSessionCount = 1);
	virtual ~ClientService();

	virtual bool Start() override;
};


 /**
  * Server Service
  */

class ServerService : public Service// 서버에서 실행
{
public:
	ServerService(NetAddress targetAddress, IocpCoreRef core, SessionFactory factory, int32 maxSessionCount = 1);
	virtual ~ServerService();

	virtual bool Start() override;
	virtual void CloseService() override;

private:
	ListenerRef _listener = nullptr;
};
