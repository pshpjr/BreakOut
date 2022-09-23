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
		cout << "matching Start" << endl;
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
	wrap(OUT _count, 0, 30);
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
		cout << "match Ready" << endl;
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
	wrap(OUT _count, 0, 30);
	drawText("Waiting... " + s, GM->_width + GM->_width / 3, GM->_height * 0.2);

	for (auto& i : GM->_pongs)
	{
		i->Render();
	}

}

void GameReady::HandleInput(GameManager* GM)
{
	if (isKeyPressing(VK_SPACE))
	{
		cout << "GameStart" << endl;
		GM->ChangeState(Playing::instance());
	}
}

void Playing::Render(GameManager* GM)
{
	if (_count == 2) {
		for (int j = 0; j < 3; j++)
		{
			for (auto& i : GM->_pongs)
			{
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
	}

	_count++;
	wrap(_count, 0, 3);
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
		cout << "Win!!" << endl;
		GM->ChangeState(Win::instance());
	}
}

void Win::Render(GameManager* GM)
{
	UIState::Render(GM);
	drawText("You are Winner!!", GM->_width + GM->_width / 3, GM->_height * 0.2);
	drawText("(Press the Space to go to lobby.)", GM->_width + GM->_width / 3, GM->_height * 0.2 - 24);
	

	for (auto& i : GM->_pongs)
	{
		i->Render();
	}
}

void Win::HandleInput(GameManager* GM)
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
