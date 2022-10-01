#include "pch.h"
#include "ClientSession.h"

#include "BreakoutPacketHandler.h"
#include "fstream"

const int KEY_LENGTH = 5;
std::string random_string(std::string::size_type length)
{
	static auto& chrs = "0123456789"
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	thread_local static std::mt19937 rg{ std::random_device{}() };
	thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

	std::string s;

	s.reserve(length);

	while (length--)
		s += chrs[pick(rg)];

	return s;
}
string GetKey()
{
	string key;
	std::ifstream fin("key.txt");

	if (fin.fail())
	{
		std::ofstream fout("key.txt");
		key = random_string(KEY_LENGTH);

		fout << key;
		fout.close();

		return key;
	}

	fin >> key;

	fin.close();

	return key;
}

ClientSession::~ClientSession()
{
	cout << "~client" << endl;
}

void ClientSession::OnConnected()
{
	string key = GetKey();
	//if (noGUI == true)
	//	key = random_string(KEY_LENGTH);

	cout << "connected" << endl;
	Protocol::C_LOGIN pkt;
	pkt.set_usercode(key);
	auto sendBuffer = BreakoutPacketHandler::MakeSendBuffer(pkt);
	Send(sendBuffer);
}

void ClientSession::OnSend(int32 len)
{
	
}

void ClientSession::OnDisconnected()
{
	PacketSession::OnDisconnected();
}

void ClientSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	BreakoutPacketHandler::HandlePacket(buffer, len);
}
