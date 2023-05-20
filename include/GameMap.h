#pragma once

#include <vector>
#include <stack>
#include <unordered_map>
#include <functional>
#include "GameObject.h"

using std::vector;
using std::stack;
using std::unordered_map;
using std::function;

class GameMap;
class GameObjectStack;
class MapInitializer;

using MapID = string;
using AutoGameObject = shared_ptr<GameObject>;
using AutoGameMap = unique_ptr<GameMap>;
using AutoMapInit = unique_ptr<MapInitializer>;
using GameMapGrid= vector<vector<GameObjectStack>> ;

class GameObjectStack {
public:
    //将GameObject添加到栈顶
    void Push(AutoGameObject obj);

    //从栈顶移除GameObject
    void  Pop();

    //查看栈顶的GameObject
    AutoGameObject Top()const;

    //返回栈是否为空
    bool IsEmpty()const;
private:
    stack<AutoGameObject> _stack;
};


class GameMap {
public:
    GameMap(const MapID& id, int rows, int cols,AutoMapInit init);
    //初始化地图
    void initMap();

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

    //获取某个位置的栈顶GameObject
    AutoGameObject GetGameObject(const Location& location)const;

    // 在某个位置上移动GameObject
    //先移除，后添加
    void MoveGameObject(const Location& from, const Location& to);

    // 在某个位置上删除栈顶GameObject
    void RemoveGameObject(const Location& location);

    // 在某个位置的栈顶添加GameObject
    void AddGameObject(AutoGameObject object, const Location& location);

    // 在某个位置上替换GameObject
    //先移除，然后添加
    void ReplaceGameObject(AutoGameObject object, const Location& location);

    // 打印地图
    void Print() const;
    //获取地图网格
    const GameMapGrid& GetMapGrid()const;
private:
    MapID _id;//地图id
    const int _rows, _cols;//行、列
    GameMapGrid _grid;//地图网格
    AutoMapInit _initFunc;//初始化

};

//用于设计map的初始化函数
class MapInitializer {
public:
    virtual ~MapInitializer() = default;
    virtual void initialize(GameMap& map) = 0;
};

//默认地图
class DefaultMapInitializer : public MapInitializer {
public:
    void initialize(GameMap& map) override;
};



// 地图的单例简单工厂类
class GameMapFactory {
public:
    //获取句柄
    static GameMapFactory& getInstance();
    //创建地图
    AutoGameMap Create(const MapID& id, int rows, int cols,AutoMapInit init);
    //根据配置文件创建地图
    AutoGameMap createFromConf();



private:
    GameMapFactory(const GameMapFactory&) = delete;
    void operator=(const GameMapFactory&) = delete;
    GameMapFactory();
};

