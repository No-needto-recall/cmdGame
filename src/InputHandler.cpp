#include "InputHandler.h"
#include "Log.h"



AutoCmd& InputHandler::handleInput() {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	FlushConsoleInputBuffer(hStdin);
	INPUT_RECORD inputRecord;
	DWORD numRead;
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
					LOG_INFO("nothing");
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
