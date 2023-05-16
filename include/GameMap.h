#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <string>

using namespace std;

#define DEFAULT_MAP  '_'

//前置声明
class Role;
class ScreenDrawer;
struct Location;

using AutoRole = shared_ptr<Role>;
using LocationString = string;
using MapID = string;


class GameMap
{
public:
	GameMap(int maxRows, int maxColumns,const MapID& mapid);
	~GameMap();
	//获取行
	int getMaxRows()const;
	//获取列
	int getMaxColumns()const;

	//获取地图ID
	MapID getMapID()const;
	//设置地图ID
	void setMapID(const MapID& mapid);


	//初始化地图
	void initMap();
	//打印地图
	void display();
	
	//添加角色
	void addRole(AutoRole actor);
	//删除角色
	void deleteRole(Role& actor);
	//移动角色
	void moveRole(Role& role, const Location& newLocation);

	//判断该坐标是否有角色
	//如果有返回该对象的指针，如果没有返回nullptr
	bool isRole(const Location & location);
	//获取该位置的对象
	AutoRole getRole(const Location & location);
	//判断该位置是否在地图内
	bool isInMap(const Location & location)const;

	//获取一个地图中没有碰撞的位置
	Location randomCollisionFreePosition();
	//在随机无碰撞位置添加角色
	void randomAddRoleWithNoCollision(AutoRole role);

	//发生碰撞
	//lhs 主动碰撞到 rhs
	void roleCollide(Role& lhs, Role& rhs);
	

private:

	int _maxRows;//最大行数
	int _maxColumns;//最大列数
	MapID _mapID;//地图名称
	vector < vector<char> > _mapData;//地图数据
	unordered_map<LocationString, AutoRole> _mapRoles;//角色信息

};

