#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <random>
#include "ScreenDrawer.h"
#include "Actor.h"
#include "Type.h"

using namespace std;

#define PLAYER_MAP 'P'
#define MONSTER_MAP 'M'
#define DEFAULT_MAP  '_'

class Actor;
using AutoActor = shared_ptr<Actor>;


class GameMap
{
public:
	GameMap(int maxRows = 20, int maxColumns = 20);
	~GameMap();
	//获取行
	int getMaxRows()const;
	//获取列
	int getMaxColumns()const;

	//初始化地图
	void initMap();
	//打印地图
	void display();
	
	//添加角色
	void addActor(AutoActor& actor);

	//删除角色
	void deleteActor(Actor* actor);

	//移动角色
	void moveActor(Actor* actor, int newX, int newY);

	//判断该坐标是否有角色
	//如果有返回该对象的指针，如果没有返回nullptr
	bool isActor(int x, int y);
	//获取位置的对象
	AutoActor& getActor(int x, int y);

	//判断该坐标是否在地图内
	bool isInMap(int x, int y)const;

	//生成a,b闭区间内的随机数
	int randomNum(int a, int b);
	//随机生成怪物
	void randomMonster();
	//战斗,lhs先手
	void fight(Actor& lhs, Actor& rhs);
	
	//获取quit
	bool getQuit()const;
	void setQuit(bool );

	//actor类型于图标转化
	char typeTomap(Type ty);
	//将x,y转化为键
	string positionToString(int x, int y);
private:
	
	bool _isQuit = true;
	int _maxRows;//最大行数
	int _maxColumns;//最大列数
	vector < vector<char> > _mapData;//地图数据
	unordered_map<string, AutoActor> _actors;//角色信息

};

