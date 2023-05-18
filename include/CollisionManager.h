#pragma once

#include "GameObject.h"


//前置声明
class GameMap;

class CollisionManager {
public:
	//检测在某张地图，某个位置是否需要碰撞处理
	bool CollisionDetection(const Location& location,GameMap& map);
	//能否在碰撞处理后移动
	bool CanItMoveAfterCollision(const Location& location, GameMap& map);
private:

};
