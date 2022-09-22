#include "pch.h"
#include "UiState.h"
#include "GameManager.h"


void UIState::Render(GameManager* GM)
{
	glViewport(GM->_width, 0, GM->_width, GM->_height);
	glLoadIdentity();

	glOrtho(GM->_width, GM->_width * 2 ,0, GM->_height, -2, 2);
	drawText("Breakout 99", GM->_width + GM->_width / 3, GM->_height * 0.9);
}

void Lobby::Render(GameManager* GM)
{
	glClearColor(1, 1, 1, 1);
	UIState::Render(GM);
	GM->_mainPlay->Render();

	drawText("press Space to start Matching", GM->_width + GM->_width/3, GM->_height * 0.2);
	drawText("ESC : exit", GM->_width + GM->_width / 3, GM->_height * 0.2 - 24);
}

void Lobby::HandleInput(GameManager* GM)
{
	if (isKeyPressing(VK_SPACE))
	{
		GM->ChangeState(Matching::instance());
	}
}

void Matching::Render(GameManager* GM)
{

	GM->_mainPlay->Render();
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
	clamp(OUT _count, 0, 30);
	drawText("Matching... " +s, GM->_width + GM->_width / 3, GM->_height * 0.2);
	drawText("(press S to stop)", GM->_width + GM->_width / 3, GM->_height * 0.2-24);
}

void Matching::HandleInput(GameManager* GM)
{
	if (isKeyPressing('S'))
	{
		GM->ChangeState(Lobby::instance());
	}

	if(isKeyPressing('M'))
	{
		GM->ChangeState(GameReady::instance());
	}
}

void GameReady::Render(GameManager* GM)
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
	clamp(OUT _count, 0, 30);
	drawText("Waiting... " + s, GM->_width + GM->_width / 3, GM->_height * 0.2);

	for (auto& i : GM->_pongs)
	{
		i->Render();
	}

}

void GameReady::HandleInput(GameManager* GM)
{
	if (isKeyPressing('G'))
	{
		GM->ChangeState(Playing::instance());
	}
}

void Playing::Render(GameManager* GM)
{
	for (auto &i : GM->_pongs)
	{
		i->Tick();
	}
}

void Playing::HandleInput(GameManager* GM)
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
		GM->ChangeState(Win::instance());
	}
}

void Win::Render(GameManager* GM)
{
	UIState::Render(GM);
	drawText("You are Winner!!", GM->_width + GM->_width / 3, GM->_height * 0.2);
	drawText("(Press the L to go to lobby.)", GM->_width + GM->_width / 3, GM->_height * 0.2 - 24);

	for (auto& i : GM->_pongs)
	{
		i->Render();
	}
}

void Win::HandleInput(GameManager* GM)
{
	if (isKeyPressing('L'))
	{
		for (auto i : GM->_pongs)
		{
			i->Reset();
		}
		GM->ChangeState(Lobby::instance());
	}
}