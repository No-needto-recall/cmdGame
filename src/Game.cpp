#include <functional> 
#include "Game.h"
#include "CollisionManager.h"
#include "Config.h"
#include "Log.h"
#include "ScreenDrawer.h"


Game::Game()
{
	loadControl();
	loadGameManager();
	loadGamePlayer();
}


Game::~Game()
{
}



void Game::start() {
	LOG_INFO("game start");
	_gameManager.GetCurrentMap()->Print();
	ScreenDrawer::getInstance().swapBuffers();
	while (1)
	{
		_Control.handleInput()->execute(_player);
		_gameManager.GetCurrentMap()->Print();
		ScreenDrawer::getInstance().swapBuffers();
	}
}

void Game::loadGamePlayer()
{
	//根据配置文件获取玩家当前所在关卡、地图、位置
	GameLevel* nowLevel = _gameManager.GetNonConstLevel(
						Config::instance().getConfigData().player.levelID);
	GameMap* nowMap = nowLevel->GetNonConstMap(
						Config::instance().getConfigData().player.mapID);
	Location nowLoc = {
		Config::instance().getConfigData().player.x,
		Config::instance().getConfigData().player.y,
	};
	AutoGameObject obj = GameObjectFactory::getInstance().createPlayerFromConf(nowLoc);
	//将玩家的obj添加到对应地图中
	nowMap->AddGameObject(obj,nowLoc);
	//创建玩家
	AutoGamePlayer player(new
		GamePlayer(
			Config::instance().getConfigData().player.name,
			nowLevel, nowMap, nowLoc, obj,
			AutoCollisionManager(new CollisionManager())
			));
	//绑定玩家
	_player = player;
	_gameManager.BindPlayer(_player);
	
}

void Game::loadGameManager()
{
	//新建一个关卡
	AutoGameLevel level(new GameLevel(
		Config::instance().getConfigData().game.levels[0].levelid));
	//添加默认地图
	level->AddMap(
		GameMapFactory::getInstance().createFromConf()
	);
	//添加关卡
	_gameManager.AddLevel(std::move(level));
}




void Game::loadControl() {
	_Control.setButtonA(std::make_unique<leftMove>());
	_Control.setButtonD(std::make_unique<rightMove>());
	_Control.setButtonW(std::make_unique<upMove>());
	_Control.setButtonS(std::make_unique<downMove>());
	_Control.setButtonQ(std::make_unique<Quit>());
	_Control.setNothing(std::make_unique<Nothing>());
}
