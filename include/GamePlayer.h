#pragma once

#include <string>
#include <memory>

using std::string;
using std::shared_ptr;
using std::unique_ptr;

//前置声明
struct Location;
class GameObject;
class GameMap;
class GameLevel;
class CollisionManager;

//类型别名
using AutoGameObject = shared_ptr<GameObject>;
using AutoCollisionManager= unique_ptr<CollisionManager>;

class GamePlayer {
public:
	GamePlayer(const string& name);

	//获取名字
	const string& GetName()const;
	//设置名字
	void SetName(const string& name);

	//获取自身object
	AutoGameObject GetObjectSelf()const;
	//根据位置获取当前所在地图的object
	AutoGameObject GetObjectWithLocation(const Location&)const;

	//移动
	void MoveToLocation(const Location&);
	void UpMove();
	void DownMove();
	void LeftMove();
	void RightMove();



private:
	string _name;
	GameLevel* _levelNow;//当前所在的关卡
	GameMap* _mapNow;//当前所在的地图
	AutoGameObject _myObject;//自身的object
	AutoCollisionManager _myCollision;//绑定的碰撞逻辑
};
