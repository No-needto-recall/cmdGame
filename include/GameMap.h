#pragma once

#include <vector>
#include <unordered_map>
#include "GameObject.h"

using std::vector;
using std::unordered_map;

class GameMap;

using MapID = string;
using AutoGameObject = shared_ptr<GameObject>;
using AutoGameMap = unique_ptr<GameMap>;
using GameMapGrid= vector<vector<AutoGameObject>> ;

class GameMap {
public:
    GameMap(const MapID& id, int rows, int cols);
    // 获取地图的ID
    const MapID& GetID() const;
    // 获取地图的行数
    int GetRows() const;
    // 获取地图的列数
    int GetCols() const;

    // 检查某个位置是否有GameObject
    bool HasGameObject(const Location& location) const;

    //检测这个位置是否在地图内
    bool InGameMap(const Location& location)const;

    //获取某个位置的GameObject
    AutoGameObject GetGameObject(const Location& location)const;

    // 在某个位置上移动GameObject
    void MoveGameObject(const Location& from, const Location& to);

    // 在某个位置上删除GameObject
    void RemoveGameObject(const Location& location);

    // 在某个位置上添加GameObject
    void AddGameObject(AutoGameObject object, const Location& location);

    // 在某个位置上替换GameObject
    void ReplaceGameObject(AutoGameObject object, const Location& location);

    // 打印地图
    void Print() const;


private:
    MapID _id;
    int _rows, _cols;
    GameMapGrid _grid;
};

// 地图的工厂类
class GameMapFactory {
public:
    //创建地图
    AutoGameMap Create(const MapID& id, int rows, int cols);

private:
    //存储已创建的地图
    unordered_map<MapID, AutoGameMap> _maps;
};


