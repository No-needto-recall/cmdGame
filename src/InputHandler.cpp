#include "InputHandler.h"



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
