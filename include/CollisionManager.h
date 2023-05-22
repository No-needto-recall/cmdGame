#pragma once

#include "Game.h"

//前置声明
class GameMap;
class GameLevel;

class CollisionManager {
public:
	CollisionManager(AutoGameManager gameManager);
	~CollisionManager();
	//设置
	void RebindGameManager(AutoGameManager gameManager);

	//检测在某张地图，某个位置是否需要碰撞处理
	bool CollisionDetection(AutoGameObject obj,const Location& location,GameMap& map,GameLevel& level);
	//能否在碰撞处理后移动
	bool CanItMoveAfterCollision(AutoGameObject obj,const Location& location, GameMap& map,GameLevel& level);

	//处理与传送门的碰撞
	void CollisionWithThePortal(AutoGameObject obj,const Location& location, GameMap& map,GameLevel& level);
private:
	AutoGameManager _gameManager;
};
