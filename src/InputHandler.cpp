#include "InputHandler.h"
#include "Log.h"
#include "Role.h"
#include "Behavior.h"


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
				default:
					LOG_INFO("无效的按键 "+c);
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

void InputHandler::setNothing(AutoCmd cmd)
{
	_nothing = std::move(cmd);
}

void leftMove::execute(AutoRole actor, GameMap* gameMap)
{
	actor->getBehavior()->leftMove(*gameMap);
}

void rightMove::execute(AutoRole actor, GameMap* gameMap)
{
	actor->getBehavior()->rightMove(*gameMap);
}

void upMove::execute(AutoRole actor, GameMap* gameMap)
{
	actor->getBehavior()->upMove(*gameMap);
}

void downMove::execute(AutoRole actor, GameMap* gameMap)
{
	actor->getBehavior()->downMove(*gameMap);
}

void Quit::execute(AutoRole actor, GameMap* gameMap)
{
	//退出
	LOG_INFO("主动退出游戏");
	exit(0);
}

void Nothing::execute(AutoRole actor, GameMap* gameMap)
{
}
