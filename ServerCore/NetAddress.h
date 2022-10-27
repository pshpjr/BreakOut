#pragma once


/*
 *NetAddress
 */

//ADDR_IN 매번 만들기 귀찮으니까 생성자로 편하게 만들고
//각종 헬퍼 함수들 추가. 
class NetAddress
{
public:
	NetAddress() = default;
	NetAddress(SOCKADDR_IN sockAddr);
	NetAddress(wstring ip, uint16 port);

	SOCKADDR_IN&	GetSockAddr() { return _sockAddr; }
	wstring			GetIpAddress();
	uint16			GetPort() { return ::ntohs(_sockAddr.sin_port);}

public:
	static IN_ADDR ip2Address(const WCHAR* ip);

private:
	SOCKADDR_IN _sockAddr = {};
};

