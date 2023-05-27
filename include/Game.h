#pragma once

#include "GameManager.h"
#include "GamePlayer.h"
#include "GameState.h"

using AutoGameManager = shared_ptr<GameManager>;
using AutoGameState = unique_ptr<GameState>;

class Game
{
public:
	//获取句柄
	static Game& getInstance();
	//开始游戏
	void start();
	~Game();
private:
	//加载玩家
	void loadGamePlayer();
	//配置GameManager
	void loadGameManager();
	//配置关卡
	void loadGameLevel();
	//配置地图
	void loadGameMap();
	//配置传送门
	void loadPortal();

private:
	AutoGameManager _gameManager;//管理玩家和关卡、地图的交互
	AutoGameState  _gameStates;//游戏当前状态
	AutoGamePlayer _player;//玩家
	//单例模式，构造私有，禁用赋值语句
	Game(const Game&) = delete;
	void operator = (const Game&) = delete;
	Game();
};

