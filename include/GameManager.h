#pragma once
#include "GameLevel.h"


using AutoGameLevel = unique_ptr<GameLevel>;
using AllLevels = unordered_map<LevelID, AutoGameLevel>;



class GameManager {
public:
    GameManager(GameLevel* currentLevel,
                GameMap* currentMap,
                const Location& currentLocation); // 构造函数
    ~GameManager(); // 析构函数


    // 获取当前关卡
    const GameLevel& GetCurrentLevel() const;
    // 设置当前关卡
    void SetCurrentLevel(GameLevel* newLevel);

    // 获取当前地图
    const GameMap& GetCurrentMap()const;
    //设置当前地图
    void SetCurrentMap(GameMap* newGameMap);
    // 获取当前玩家坐标
    const Location& GetCurrentLocation()const;
    //设置当前玩家坐标
    void SetCurrentLocation(const Location& newLocation);

    // 添加关卡
    void AddLevel(AutoGameLevel);
    // 删除关卡
    void DelLevel(const LevelID& id);

    //获取指定关卡、地图、位置的对象
    AutoGameObject GetObjectWith(const LevelID& levelId, const MapID& mapID, const Location& loc)const;

    // 在当前地图上操作对象
    void AddObjectCurrentMap(const Location& loc, AutoGameObject obj);     
    void RemoveObjectCurrentMap(const Location& loc);                     
    void MoveObjectCurrentMap(const Location& from, const Location& to);   
    void ReplaceGameObjectCurrentMap(AutoGameObject obj, const Location& loc); 

    // 在当前关卡的指定地图上操作对象
    void AddObjectCurrentLevel(const MapID& mapId, const Location& loc, AutoGameObject obj);     
    void RemoveObjectCurrentLevel(const MapID& mapId, const Location& loc);                     
    void MoveObjectCurrentLevel(const MapID& mapId, const Location& from, const Location& to); 
    void ReplaceGameObjectCurrentLevel(const MapID& mapId, AutoGameObject obj, const Location& loc); 

    // 在指定关卡和地图上操作对象
    void AddObject(const LevelID& levelId, const MapID& mapId, 
                   const Location& loc, AutoGameObject obj);     
    void RemoveObject(const LevelID& levelId, const MapID& mapId, const Location& loc);                     
    void MoveObject(const LevelID& levelId, const MapID& mapId, 
                    const Location& from, const Location& to); 
    void ReplaceGameObject(const LevelID& levelId, const MapID& mapId,
                            AutoGameObject obj, const Location& loc); 
    void MoveObjectMapToMap(const LevelID& fromLevelId, const MapID& fromMapId, 
                            const LevelID& toLevelId, const MapID& toMapId, 
                            const Location& from, const Location& to); 

    //将当前玩家，移动到另一个关卡的地图中
    void CurrentMoveToOtherMap(const LevelID& toLevelId,const MapID& toMapID,
                               const Location to);


private:
    AllLevels  _levels; // 所有关卡
    GameLevel* _currentLevel; // 当前玩家所在的关卡
    GameMap* _currentMap;//当前玩家所在的地图
    Location _currentLocation;//当前玩家的坐标
};

