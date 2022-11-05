#include "pch.h"
#include "Player.h"

#include <utility>

void Player::Send(SendBufferRef buffer) const
{
	if(_connected == false)
		return;

	_session->Send(std::move(buffer));
}
