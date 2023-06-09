#pragma once

#include <string>
#include <memory>
#include "GameObject.h"
#include "PokemonBox.h"

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
using AutoPokemonBox = unique_ptr<PokemonBox>;

class GamePlayer {
public:
	GamePlayer(const string& name,GameLevel* levelNow,GameMap* mapNow,
			   const Location& location,AutoGameObject selfObject , 
				const int& sight,  AutoCollisionManager collision);

	//获取名字
	const string& GetName()const;
	//设置名字
	void SetName(const string& name);

	//获取当前相关信息
	const GameLevel* GetLevel()const;
	const GameMap* GetMap()const;
	const Location& GetLocation()const;
	GameLevel* GetNonConstLevel();
	GameMap* GetNonConstMap();
	Location& GetNonConstLocation();
	//设置当前相关信息
	void SetLevel(GameLevel* level);
	void SetMap(GameMap* map);
	void SetLocation(const Location& location);


	//获取自身object
	AutoGameObject GetObjectSelf()const;
	//根据位置获取当前所在地图的object
	AutoGameObject GetObjectWithLocation(const Location&)const;

	//获取视距
	int GetLineOfSight()const;
	//设置视距
	void SetLineOfSight(const int& sight);

	//移动
	void MoveToLocation(const Location&);
	//真实调用移动
	void RealMove(const Location&);
	void UpMove();
	void DownMove();
	void LeftMove();
	void RightMove();

	//添加宝可梦
	void AddPokemon(AutoPokemon pokemon);
	//移除宝可梦
	void RemovePokemon(int id);
	//获取当前参战的宝可梦的id集合
	vector<int> GetBattlePokemonIds()const;
	//通过宝可梦id ,获取宝可梦指针
	AutoPokemon GetPokemonById(int id)const;

private:
	string _name;
	GameLevel* _levelNow;//当前所在的关卡
	GameMap* _mapNow;//当前所在的地图
	Location _locationNow;//当前的坐标值
	AutoGameObject _myObject;//自身的object
	int _lineOfSight;//视距
	AutoCollisionManager _myCollision;//绑定的碰撞逻辑
	AutoPokemonBox _pokemonBox; //宝可梦存储器
};

//玩家类单例工厂
class GamePlayerFactory {

};
