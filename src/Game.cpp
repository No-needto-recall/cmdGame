#include "Game.h"
#include "Config.h"



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
	AutoActor player(new Player(
		Config::instance().getConfigData().actor.player.health,
		Config::instance().getConfigData().actor.player.mana,
		Config::instance().getConfigData().actor.player.attack, 
		Config::instance().getConfigData().actor.player.defense, 
		5, 5, Type::PLAYER,
		Config::instance().getConfigData().actor.player.name
	));
	_gameMap.addActor(player);
	_gameMap.randomMonster();
	_gameMap.display();
	while (_gameMap.getQuit()) {
		_Control.handleInput().get()->execute(*player);
		_gameMap.display();
		ScreenDrawer::getInstance().swapBuffers();
		ScreenDrawer::getInstance().clearScreen();
	}
	system("pause");
}


void Game::loadMap() {
	_gameMap.initMap();
}


void Game::loadControl() {
	_Control.setButtonA(std::make_unique<leftMove>());
	_Control.setButtonD(std::make_unique<rightMove>());
	_Control.setButtonW(std::make_unique<upMove>());
	_Control.setButtonS(std::make_unique<downMove>());
	_Control.setButtonQ(std::make_unique<Quit>());
	_Control.setNothing(std::make_unique<Nothing>());
}
