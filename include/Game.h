#pragma once

#include "InputHandler.h"
#include "GameManager.h"

using std::shared_ptr;


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
	GameManager _gameManager;
	InputHandler _Control;
};

