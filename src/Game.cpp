#include <functional> 
#include "Game.h"
#include "Config.h"
#include "Log.h"
#include "ScreenDrawer.h"
#include "Role.h"
#include "Behavior.h"
#include "CreatFromConfig.h"


Game::Game()
	:_gameMap(new GameMap(
		Config::instance().getConfigData().game.maps[0].maxRows,
		Config::instance().getConfigData().game.maps[0].maxColumns,
		Config::instance().getConfigData().game.maps[0].mapid
		)
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
	_gameMap->randomCreatRole();
	_gameMap->display();
	ScreenDrawer::getInstance().swapBuffers();
	
	//创建角色
	AutoRole player = CreatRole::creatPlayerRoleFromConfig(_gameMap);
	//添加到地图
	_gameMap->addRole(player);
	while (1) {
		_Control.handleInput()->execute(player);
		_gameMap->display();
		ScreenDrawer::getInstance().swapBuffers();
		ScreenDrawer::getInstance().clearScreen();
	}
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
