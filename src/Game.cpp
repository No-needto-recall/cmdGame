#include "Game.h"
#include "Config.h"
#include "Log.h"
#include "ScreenDrawer.h"
#include "Role.h"
#include "Behavior.h"



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

	char icon = Config::instance().getConfigData().role.player.icon;
	AutoRole player(new PlayerRole(
		{
		Config::instance().getConfigData().role.player.name,
		Config::instance().getConfigData().role.player.health,
		Config::instance().getConfigData().role.player.mana,
		Config::instance().getConfigData().role.player.attack,
		Config::instance().getConfigData().role.player.defense,
		icon
		},
		{
		Config::instance().getConfigData().role.player.spawnX,
		Config::instance().getConfigData().role.player.spawnY,
		},
		_gameMap
		));

	std::unique_ptr<Behavior> tmpPlayerBehavior(new PlayerBehavior(*player));
	player->setBehavior(std::move(tmpPlayerBehavior));
	_gameMap.addRole(player);
	while (1) {
		_Control.handleInput()->execute(player.get(), &_gameMap);
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
