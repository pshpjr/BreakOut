#include "pch.h"
#include "UiState.h"
#include "Client.h"
#include "Service.h"
#include "BreakoutPacketHandler.h"
void UIState::Render(Client* GM)
{
	glViewport(0, 0, GM->SCREENWIDTH, GM->SCREENHEIGHT);
	glLoadIdentity();

	glOrtho(0, GM->SCREENWIDTH, 0, GM->SCREENHEIGHT, -2, 2);
	drawText("Breakout 99", GM->SCREENWIDTH * center , GM->baseHeight * topHRate);
}

void Lobby::Render(Client* GM)
{
	glClearColor(1, 1, 1, 1);
	UIState::Render(GM);
	drawText("press Space to start Matching", GM->SCREENWIDTH * center, GM->SCREENHEIGHT * bottomHRate);
	drawText("ESC : exit", GM->SCREENWIDTH * center, GM->SCREENHEIGHT * bottomHRate - 24);

	GM->_mainPlay->Render();
}

void Lobby::HandleInput(Client* GM)
{
	if (isKeyPressing(VK_SPACE))
	{
		Protocol::C_MACHING_GAME pkt;
		GM->_service->Broadcast(BreakoutPacketHandler::MakeSendBuffer(pkt));
		cout << "matching Start" << endl;
	}
}

void Matching::Render(Client* GM)
{
	UIState::Render(GM);
	string s;

	switch (_count / 3)
	{
	case 0:
		s = "/";
		break;
	case 1:
		s = "--";
		break;
	case 2:
		s = "\\";
		break;
	}
	_count++;
	wrap(OUT _count, 0, 30);
	drawText("Matching... " +s, GM->SCREENWIDTH * center, GM->SCREENHEIGHT * bottomHRate);
	drawText("(press S to stop)", GM->SCREENWIDTH * center, GM->SCREENHEIGHT * bottomHRate-24);

	GM->_mainPlay->Render();
}

void Matching::HandleInput(Client* GM)
{
	if (isKeyPressing('S'))
	{
		GM->ChangeState(Lobby::instance());
	}

}

void GameReady::Render(Client* GM)
{
	UIState::Render(GM);
	string s;

	switch (_count / 3)
	{
	case 0:
		s = "/";
		break;
	case 1:
		s = "--";
		break;
	case 2:
		s = "\\";
		break;
	}
	_count++;
	wrap(OUT _count, 0, 30);
	drawText("Waiting... " + s, GM->SCREENWIDTH * center, GM->SCREENHEIGHT * bottomHRate);

	for (auto& i : GM->_pongs)
	{
		i->Render();
	}

}

void GameReady::HandleInput(Client* GM)
{
}

void Playing::Render(Client* GM)
{

	_count++;
	wrap(_count, 0, 3);

	int players = 0;
	if (_count == 2) {
		for (int j = 0; j < 3; j++)
		{
			for (auto& i : GM->_pongs)
			{
				if(i->isDead())
					continue;
				if (i == GM->_mainPlay)
					continue;
				i->Update();
				
			}
		}
	}

	GM->_mainPlay->Update();

	for (auto& i : GM->_pongs)
	{
		i->Render();
		if (i->isDead() == false)
			players++;
	}

	if (players == 1)
		GM->ChangeState(Win::instance());

	glViewport(0, 0, GM->SCREENWIDTH, GM->SCREENHEIGHT);
	glLoadIdentity();

	glOrtho(0, GM->SCREENWIDTH, 0, GM->SCREENHEIGHT, -2, 2);

	drawText("Life: " + std::to_string(GM->_mainPlay->_life), GM->SCREENWIDTH * 0.4, GM->baseHeight * topHRate - 24);
	drawText(std::to_string(players) + "/99", GM->SCREENWIDTH * 0.6, GM->baseHeight * topHRate);

}

void Playing::HandleInput(Client* GM)
{
	if (isKeyPressing('A'))
	{
		for (auto &i : GM->_pongs)
		{
			i->_control_block->setVector({ -1,0 });
			i->_control_block->setSpeed(GM->CONTROLBLOCKSPEED);
		}
	}
	if (isKeyPressing('D'))
	{
		for (auto i : GM->_pongs)
		{
			i->_control_block->setVector({ 1,0 });
			i->_control_block->setSpeed(GM->CONTROLBLOCKSPEED);
		}
	}
	if (isKeyPressing('V'))
	{
		cout << "Win!!" << endl;
		GM->ChangeState(Win::instance());
	}
}

void Win::Render(Client* GM)
{
	UIState::Render(GM);
	drawText("You are Winner!!", GM->SCREENWIDTH * center, GM->SCREENHEIGHT * bottomHRate);
	drawText("(Press the Space to go to lobby.)", GM->SCREENWIDTH * 0.4, GM->SCREENHEIGHT * bottomHRate - 24);
	

	for (auto& i : GM->_pongs)
	{
		i->Render();
	}
}

void Win::HandleInput(Client* GM)
{
	if (isKeyPressing(VK_SPACE))
	{
		for (auto i : GM->_pongs)
		{
			i->Reset();
		}
		cout << "Goto Lobby" << endl;
		GM->ChangeState(Lobby::instance());
		Sleep(300);
	}
}
