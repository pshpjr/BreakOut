#include "pch.h"
#include "Player.h"
#include "ServerPacketHandler.h"
void Player::Update()
{
	_breakout.Update();
}

void Player::ResetBreakout()
{
	_breakout.Reset();
}

void Player::HandleInput(Protocol::KeyInput input)
{
	
}

void Player::SendDead(int32 rank)
{
	Protocol::S_END pkt;

	pkt.set_rank(rank);

	Send(ServerPacketHandler::MakeSendBuffer(pkt));
}

void Player::SendWin()
{
	SendDead(1);
}
