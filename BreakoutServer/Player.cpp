#include "pch.h"
#include "Player.h"

#include "Objects.h"
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
	bool direction = input.direction();
	bool onOff = input.onoff();

	_breakout.SetControlBlockMovable(onOff);

	_breakout.SetControlBlockVector(direction);
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
