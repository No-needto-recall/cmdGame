#include "Game.h"
#include "Config.h"
#include "Log.h"
#include "ScreenDrawer.h"
#include "Role.h"
#include "Behavior.h"
#include "CreatFromConfig.h"



Game::Game()
	:_gameMap(
		Config::instance().getConfigData().game.map.maxRows,
		Config::instance().getConfigData().game.map.maxColumns
	)
{
	loadMap();
	loadControl();
}


Game::~Game()
{
}



void Game::start() {
	LOG_INFO("\n\ngame start");
	_gameMap.randomCreatRole();
	_gameMap.display();
	ScreenDrawer::getInstance().swapBuffers();

	AutoRole player = CreatRole::creatPlayerFromConfig();
	AutoBehavior  tmpPlayerBehavior = CreatBehavior::creatPlayerBehaviorFromConfig(player);
	player->setBehavior(std::move(tmpPlayerBehavior));
	player->setGameMap(std::make_shared<GameMap>( _gameMap));
	_gameMap.addRole(player);
	while (1) {
		_Control.handleInput()->execute(player, &_gameMap);
		_gameMap.display();
		ScreenDrawer::getInstance().swapBuffers();
		ScreenDrawer::getInstance().clearScreen();
	}
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
