#pragma once

#include "GameMap.h"


using LevelID = string;
using AllMaps = unordered_map<MapID, AutoGameMap>;

class GameLevel {
public:

	GameLevel(LevelID id);
	~GameLevel();
	const LevelID& GetID()const;


	//添加地图
	void AddMap(AutoGameMap);
	//删除地图
	void DelMap(const MapID&);
	//获取地图
	const GameMap* GetMap(const MapID&)const;
	//获取可被修改的地图
	GameMap* GetNonConstMap(const MapID& id);
	//获取地图的行数
	int GetMapRows(const MapID&)const;
	//获取地图的列数
	int GetMapCols(const MapID&)const;

	//获取指定地图、指定位置的GameObject
	AutoGameObject GetObjectWith(const MapID&, const Location&)const;

	//在指定地图、指定位置、添加GameObject
	void AddObjectWith(const MapID&, const Location&, AutoGameObject);
	//在指定地图、指定位置、删除GameObject
	void RemoveObjectWith(const MapID&, const Location&);
	//在指定地图、将某个位置的GameObject移动到另一个位置
	void MoveObjectWith(const MapID&, const Location& from, const Location& to);
	//在指定地图的某个位置，替换GameObject
	void ReplaceGameObject(const MapID&, AutoGameObject object, const Location& location);

	//将某个地图某个位置的object 移动到 另一张地图的另一个位置
	void MoveObjectMapToMap(const MapID& fromId, const MapID& toID,
		const Location& from, const Location& to);


private:

	LevelID _id;//关卡id
	AllMaps _maps;//持有的地图

};
