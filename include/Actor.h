#pragma once
#include "Log.h"
#include "GameMap.h"

using namespace std;

class GameMap;

class Actor
{
public:

	Actor(int hp = 0, int mp = 0
		, int attack = 0, int defense = 0
		, int x = 0, int y = 0
		, const string& name = "null");

	virtual ~Actor();
	//获取x,y
	int getX()const;
	int getY()const;
	//设置x,y
	void setX(const int& x);
	void setY(const int& y);

	//获取名称
	string getName()const;
	//设置名称
	void setName(const string& str);

	//是否存活
	bool isAlive();
	//是否死亡
	bool isDeath();

	//普通攻击
	void AD_attack(Actor& target);

	//获取坐标信息
	string getPosition();

	//绑定地图
	void bindMap(GameMap* gMap);
	//获取地图
	GameMap* getMap();

	virtual void left();
	virtual void right();
	virtual void up();
	virtual void down();
protected:

	int _hp;//生命值
	int _mp;//法力值
	int _attackPower;//攻击力
	int _defensePower;//防御力
	int _x;//x坐标
	int _y;//y坐标
	string _name;//名称
	GameMap* _gMap;//所处在的地图

};

