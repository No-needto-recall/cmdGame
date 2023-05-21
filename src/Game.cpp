#include <functional> 
#include "Game.h"
#include "Config.h"
#include "Log.h"
#include "ScreenDrawer.h"


Game::Game()
{
	loadMap();
	loadControl();
}


Game::~Game()
{
}



void Game::start() {
	LOG_INFO("\n\ngame start");
}


void Game::loadMap() {
	_gameMap->initMap();
}


void Game::loadControl() {
	_Control.setButtonA(std::make_unique<leftMove>());
	_Control.setButtonD(std::make_unique<rightMove>());
	_Control.setButtonW(std::make_unique<upMove>());
	_Control.setButtonS(std::make_unique<downMove>());
	_Control.setButtonQ(std::make_unique<Quit>());
	_Control.setNothing(std::make_unique<Nothing>());
}
