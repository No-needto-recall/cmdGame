#pragma once
#include "GameLevel.h"

//前置声明
class GamePlayer;

using AutoGameLevel = unique_ptr<GameLevel>;
using AutoGamePlayer = shared_ptr<GamePlayer>;
using AllLevels = unordered_map<LevelID, AutoGameLevel>;


class GameManager {
public:
    GameManager(AutoGamePlayer player = nullptr);//构造函数
    ~GameManager(); // 析构函数

    // 获取当前关卡、地图、坐标
    const GameLevel* GetCurrentLevel() const;
    GameLevel* GetNonConstCurrentLevel() ;
    const GameMap* GetCurrentMap()const;
    GameMap* GetNonConstCurrentMap();
    const Location& GetCurrentLocation()const;
    Location& GetNonConstCurrentLocation();
    //设置当前关卡、地图、坐标
    void SetPlayerLevel(GameLevel*);
    void SetPlayerMap(GameMap*);
    void SetPlayerLocation(const Location&);

    //绑定玩家
    void BindPlayer(AutoGamePlayer player);
    //获取绑定的玩家
    const GamePlayer* GetPlayer()const;
    GamePlayer* GetNonConstPlayer();


    // 添加关卡
    void AddLevel(AutoGameLevel);
    // 删除关卡
    void DelLevel(const LevelID& id);
    //获取关卡
    const GameLevel* GetLevel(const LevelID& id);
    GameLevel* GetNonConstLevel(const LevelID& id);

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
    AutoGamePlayer _player;//管理的玩家
    static Location defaultLocation ;//用于处理异常
};



