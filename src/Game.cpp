#include <functional> 
#include "Game.h"
#include "CollisionManager.h"
#include "PortalManager.h"
#include "Config.h"
#include "Log.h"
#include "ScreenDrawer.h"


Game::Game()
	:_gameManager(new GameManager())
	,_Control()
	,_player(nullptr)
{
	LOG_INFO("-----启动游戏");
	loadControl();
	loadGameManager();
	loadGamePlayer();
	loadPortal();
}


Game::~Game()
{
}



Game& Game::getInstance()
{
	static Game instance;
	return instance;
}

void Game::start() {
	LOG_INFO("game start");
	_gameManager->DrawMapWithPlayer();
	ScreenDrawer::getInstance().swapBuffers();
	while (1)
	{
		_Control.handleInput()->execute(_player);
		_gameManager->DrawMapWithPlayer();
		ScreenDrawer::getInstance().swapBuffers();
	}
}

void Game::loadGamePlayer()
{
	//根据配置文件获取玩家当前所在关卡、地图、位置
	GameLevel* nowLevel = _gameManager->GetNonConstLevel(
						CONFIG_DATA.player.levelID);
	GameMap* nowMap = nowLevel->GetNonConstMap(
						CONFIG_DATA.player.mapID);
	Location nowLoc = {
		CONFIG_DATA.player.x,
		CONFIG_DATA.player.y,
	};
	AutoGameObject obj = GameObjectFactory::getInstance().createPlayerFromConf(nowLoc);
	//将玩家的obj添加到对应地图中
	nowMap->AddGameObject(obj,nowLoc);
	//创建玩家
	AutoGamePlayer player(new
		GamePlayer(
			CONFIG_DATA.player.name,
			nowLevel, nowMap, nowLoc, obj,
			CONFIG_DATA.player.lineOfSight,
			AutoCollisionManager(new CollisionManager(_gameManager))
			));
	//绑定玩家
	_player = player;
	_gameManager->BindPlayer(_player);
	
}

void Game::loadGameManager()
{
	//新建一个关卡
	AutoGameLevel level(new GameLevel(
		Config::instance().getConfigData().game.levels[0].levelid));
	//添加地图
	level->AddMap(GameMapFactory::getInstance().CreatUnwhiteTown());
	level->AddMap(GameMapFactory::getInstance().CreatRoute101());
	//添加关卡
	_gameManager->AddLevel(std::move(level));
}

void Game::loadGameLevel()
{
}

void Game::loadGameMap()
{
}




void Game::loadPortal()
{
	for (int i = 0; i < CONFIG_DATA.game.portals.size(); ++i) {
		PortalKey key(PORTAL_MANAGER.GetKeyFromConf(i));
		PortalInfo info(PORTAL_MANAGER.GetInfoFromConf(i));

		//添加到对应的地图
		PORTAL_MANAGER.AddPortalObjectWith(key, *_gameManager);
		PORTAL_MANAGER.AddPortalObjectWith(info, *_gameManager);
		//注册到PortalManager
		PORTAL_MANAGER.AddPortal(key, info);
		PORTAL_MANAGER.AddPortal(info, key);
	}

}

void Game::loadControl() {
	_Control.setButtonA(std::make_unique<leftMove>());
	_Control.setButtonD(std::make_unique<rightMove>());
	_Control.setButtonW(std::make_unique<upMove>());
	_Control.setButtonS(std::make_unique<downMove>());
	_Control.setButtonQ(std::make_unique<Quit>());
	_Control.setNothing(std::make_unique<Nothing>());
}
