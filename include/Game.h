#pragma once

#include "GameMap.h"
#include "InputHandler.h"

using std::shared_ptr;

using AutoGameMap = shared_ptr<GameMap>;

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
	AutoGameMap _gameMap;
	InputHandler _Control;
};

