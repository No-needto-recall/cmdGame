#include "InputHandler.h"
#include "Log.h"
#include "Role.h"
#include "Behavior.h"


AutoCmd& InputHandler::handleInput() {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inputRecord;
	DWORD numRead;
	Sleep(500);//避免玩家按键频繁
	FlushConsoleInputBuffer(hStdin);
	WaitForSingleObject(hStdin, INFINITE);
	if (ReadConsoleInput(hStdin, &inputRecord, 1, &numRead)) {
		if (inputRecord.EventType == KEY_EVENT) {
			if (inputRecord.Event.KeyEvent.bKeyDown) {
				switch (inputRecord.Event.KeyEvent.wVirtualKeyCode)
				{
				case'W':
					//LOG_INFO("W");
					return _buttonW;
				case'A':
					//LOG_INFO("A");
					return _buttonA;
				case'S':
					//LOG_INFO("S");
					return _buttonS;
				case'D':
					//LOG_INFO("D");
					return _buttonD;
				case'Q':
					//LOG_INFO("Q");
					return _buttonQ;
				default:
					return _nothing;
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

void leftMove::execute(Role* actor, GameMap* gameMap)
{
	actor->getBehavior()->leftMove(*gameMap);
}

void rightMove::execute(Role* actor, GameMap* gameMap)
{
	actor->getBehavior()->rightMove(*gameMap);
}

void upMove::execute(Role* actor, GameMap* gameMap)
{
	actor->getBehavior()->upMove(*gameMap);
}

void downMove::execute(Role* actor, GameMap* gameMap)
{
	actor->getBehavior()->downMove(*gameMap);
}

void Quit::execute(Role* actor, GameMap* gameMap)
{
	//退出
	LOG_INFO("主动退出游戏");
	exit(0);
}

void Nothing::execute(Role* actor, GameMap* gameMap)
{
	LOG_INFO("无效按键");
}
