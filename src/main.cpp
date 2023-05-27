#include <iostream>
#include "Game.h"
#include "ScreenWindow.h"
using namespace std;


int main(int argc,char* argv[]) {

	Game::getInstance().start();
	return 0;
}