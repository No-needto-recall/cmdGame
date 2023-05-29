#include "InputHandler.h"
#include "Log.h"
#include "GamePlayer.h"


AutoCmd& InputHandler::handleInput() {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inputRecord;
	DWORD numRead;
	//Sleep(200);//避免玩家按键频繁
	FlushConsoleInputBuffer(hStdin);
	WaitForSingleObject(hStdin, INFINITE);
	if (ReadConsoleInput(hStdin, &inputRecord, 1, &numRead)) {
		if (inputRecord.EventType == KEY_EVENT) {
			if (inputRecord.Event.KeyEvent.bKeyDown) {
				char c = inputRecord.Event.KeyEvent.uChar.AsciiChar;
				c = tolower(c);
				switch (c)
				{
				case 'w':
					//LOG_INFO("W");
					return _buttonW;
				case 'a':
					//LOG_INFO("A");
					return _buttonA;
				case 's':
					//LOG_INFO("S");
					return _buttonS;
				case 'd':
					//LOG_INFO("D");
					return _buttonD;
				case 'q':
					//LOG_INFO("Q");
					return _buttonQ;
				case 'j':
					//LOG_INFO("Q");
					return _buttonJ;
				case 'k':
					//LOG_INFO("Q");
					return _buttonK;
				default:
					LOG_INFO("无效的按键 ");
					break;
				}
			}
		}
	}
	return _nothing;
}

void InputHandler::setButtonA(AutoCmd cmd)
{
	_buttonA = std::move(cmd);
}

void InputHandler::setButtonD(AutoCmd cmd)
{
	_buttonD = std::move(cmd);
}

void InputHandler::setButtonW(AutoCmd cmd)
{
	_buttonW = std::move(cmd);
}

void InputHandler::setButtonS(AutoCmd cmd)
{
	_buttonS = std::move(cmd);
}

void InputHandler::setButtonQ(AutoCmd cmd)
{
	_buttonQ = std::move(cmd);
}

void InputHandler::setButtonJ(AutoCmd cmd)
{
	_buttonJ = std::move(cmd);
}

void InputHandler::setButtonK(AutoCmd cmd)
{
	_buttonK = std::move(cmd);
}

void InputHandler::setNothing(AutoCmd cmd)
{
	_nothing = std::move(cmd);
}

void leftMove::execute(AutoGamePlayer actor)
{
	actor->LeftMove();
}

void rightMove::execute(AutoGamePlayer actor)
{
	actor->RightMove();
}

void upMove::execute(AutoGamePlayer actor)
{
	actor->UpMove();
}

void downMove::execute(AutoGamePlayer actor)
{
	actor->DownMove();
}

void Quit::execute(AutoGamePlayer actor)
{
	exit(1);
	LOG_INFO("主动退出游戏");
}

void Nothing::execute(AutoGamePlayer actor)
{
}

void Confirm::execute(AutoGamePlayer actor)
{
}

void Back::execute(AutoGamePlayer actor)
{
}
