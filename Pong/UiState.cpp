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

string UIState::Loading(int& count)
{
	string s = "";
	switch (count / 3)
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
	count++;
	wrap(OUT count, 0, 30);
	return s;
}

void Init::Render(Client* GM)
{
	UIState::Render(GM);
	drawText("Connect to Server... " + Loading(_count), GM->SCREENWIDTH * center, GM->SCREENHEIGHT * bottomHRate);
	
	GM->_mainPlay->Render();
}

void Init::HandleInput(Client* GM)
{
	UIState::HandleInput(GM);
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
	if (isKeyStateChanged(VK_SPACE,OUT _matchingState))
	{
		if (_matchingState == false)
			return;

		Protocol::C_MACHING_GAME pkt;
		GM->_service->Broadcast(BreakoutPacketHandler::MakeSendBuffer(pkt));
		cout << "matching Start" << endl;
	}
}

void Matching::Render(Client* GM)
{
	UIState::Render(GM);

	drawText("Matching... " +Loading(_count), GM->SCREENWIDTH * center, GM->SCREENHEIGHT * bottomHRate);
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

	drawText("Waiting... " + Loading(_count), GM->SCREENWIDTH * center, GM->SCREENHEIGHT * bottomHRate);

	for (auto& i : GM->_pongs)
	{
		i->Render();
	}

}

void GameReady::HandleInput(Client* GM)
{
}

void Playing::Update(Client* GM)
{
	//_count++;
	//wrap(_count, 0, 12);

	//if (_count == 11) {
	//	for (int j = 0; j < 11; j++)
	//	{
	//		for (auto& i : GM->_pongs)
	//		{
	//			if (i->isDead())
	//				continue;
	//			if (i == GM->_mainPlay)
	//				continue;
	//			i->Update();

	//		}
	//	}
	//}

	//GM->_mainPlay->Update();


	for (auto& i : GM->_pongs)
	{
		if (i->isDead())
			continue;
		i->Update();
	}
}

void Playing::Render(Client* GM)
{
	int players = 0;
	
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
	//¿ÞÂÊ : direction True

	if (isKeyStateChanged('A',_lState))
	{
		//auto i = GM->_mainPlay;
		//i->_control_block->setVector({ -1,0 });


		//i->_control_block->setSpeed(GM->CONTROLBLOCKSPEED);
		//if (_lState == false) {
		//	i->_control_block->setSpeed(0);
		//}

		Protocol::KeyInput* key = new Protocol::KeyInput;
		Protocol::C_MOVE pkt;


		key->set_direction(true);
		key->set_onoff(_lState);

		pkt.set_allocated_input(key);
		pkt.set_roomnumber(GM->_roomNumber);
		SendBufferRef buffer = BreakoutPacketHandler::MakeSendBuffer(pkt);

		GM->_service->Broadcast(buffer);
		
	}
	if (isKeyStateChanged('D',_rState))
	{

		//auto i = GM->_mainPlay;
		//i->_control_block->setVector({ 1,0 });

		//i->_control_block->setSpeed(GM->CONTROLBLOCKSPEED);
		//if (_rState == false)
		//	i->_control_block->setSpeed(0);

		Protocol::KeyInput* key = new Protocol::KeyInput;
		Protocol::C_MOVE pkt;

		key->set_direction(false);
		key->set_onoff(_rState);

		pkt.set_allocated_input(key);
		pkt.set_roomnumber(GM->_roomNumber);
		SendBufferRef buffer = BreakoutPacketHandler::MakeSendBuffer(pkt);

		GM->_service->Broadcast(buffer);
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
