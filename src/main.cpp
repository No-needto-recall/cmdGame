#include <iostream>
#include "Game.h"
#include "ScreenWindow.h"
using namespace std;


int main(int argc,char* argv[]) {

	ScreenWindow windows(0, 0, 10, 2);
	windows.addText("my name is huawei,today is 5.12\n do u want to play game?");
	while (1) {
		windows.displayNextPage();
		ScreenDrawer::getInstance().swapBuffers();
		Sleep(3000);
	}
	//Game::getInstance().start();
	return 0;
}