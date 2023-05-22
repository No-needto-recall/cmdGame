#pragma once

#include "InputHandler.h"
#include "GameManager.h"
#include "GamePlayer.h"


class Game
{
public:
	Game();
	~Game();

	//开始游戏
	void start();
private:
	//加载玩家
	void loadGamePlayer();
	//配置GameManager
	void loadGameManager();
	//配置关卡
	void loadGameLevel();
	//配置地图
	void loadGameMap();
	//配置控制
	void loadControl();

private:
	GameManager _gameManager;
	InputHandler _Control;
	AutoGamePlayer _player;//玩家
};

