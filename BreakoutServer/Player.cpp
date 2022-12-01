#include "pch.h"
#include "Player.h"

#include "Objects.h"
#include "ServerPacketHandler.h"
bool Player::Update()
{

	return _breakout.Update();
}

void Player::ResetBreakout()
{
	_breakout.Reset();
}

void Player::HandleInput(Protocol::KeyInput& input)
{
	bool direction = input.direction();
	bool onOff = input.onoff();

	_breakout.SetControlBlockMovable(onOff);

	_breakout.SetControlBlockVector(direction);

	if(onOff == false)
		_breakout.CompensateCBNetDelay(direction);

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

void Player::SetState(Protocol::StateU* state)
{
	string* key = new string( GetKey());
	state->set_allocated_code(key);

	auto bLocation = _breakout._b->getLocation();
	state->set_blocx(bLocation.x);
	state->set_blocy(bLocation.y);

	auto bVec = _breakout._b->getVector();
	state->set_bvecx(bVec.x);
	state->set_bvecy(bVec.y);

	auto cLoc= _breakout._control_block->getStart();
	state->set_clocx(cLoc.x);

	state->set_life(_breakout._life);

	uint64 boardState = 0;

	for(const auto& i : _breakout._blocks)
	{
		if(i->isVisible())
		{
			boardState|= 1;
		}
		else
		{
			boardState |= 0;
		}
		boardState <<= 1 ;
	}
	boardState = boardState<< 10;
	state->set_boardstate(boardState);
}
