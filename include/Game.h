#pragma once

#include "GameMap.h"
#include "InputHandler.h"

class Game
{
public:
	Game();
	~Game();

	//开始游戏
	void start();

	//配置地图
	void loadMap();
	//配置控制
	void loadControl();

private:
	GameMap _gameMap;
	InputHandler _Control;
};

