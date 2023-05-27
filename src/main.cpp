#include <iostream>
#include "Game.h"
#include "ScreenWindow.h"
using namespace std;


void test() {

	ScreenWindow window(0, 10, 20, 3);
	window.addText("想要小火龙做什么呢?\n攻击还是防御");
	while (1) {
		window.displayNextPage();
		ScreenDrawer::getInstance().swapBuffers();
		Sleep(2000);
	}
}


int main(int argc,char* argv[]) {

	std::setlocale(LC_ALL, "en_US.UTF-8");
	SetConsoleOutputCP(65001);

	Game::getInstance().start();
	return 0;
}