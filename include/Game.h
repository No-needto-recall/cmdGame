#pragma once

#include "InputHandler.h"
#include "GameManager.h"
#include "GamePlayer.h"

using AutoGameManager = shared_ptr<GameManager>;

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
	//配置控制
	void loadControl();

private:
	AutoGameManager _gameManager;
	InputHandler _Control;
	AutoGamePlayer _player;//玩家
	//单例模式，构造私有，禁用赋值语句
	Game(const Game&) = delete;
	void operator = (const Game&) = delete;
	Game();
};

