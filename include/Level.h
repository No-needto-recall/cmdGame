#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class GameMap;
class Role;
struct Location;

using std::vector;
using std::shared_ptr;
using std::string;
using std::unordered_map;


using AutoRole = shared_ptr<Role>;
using AutoGameMap = shared_ptr<GameMap>;
using MapID = string;
using LevelMaps = unordered_map<MapID,AutoGameMap>;

using LevelID = string;



class Level {
public:
    Level(const LevelID levelid);
    ~Level();

    // 添加地图到关卡
    void addMap(const AutoGameMap map);

    // 删除地图
    void removeMap(const MapID& mapId);

    //是否存在该地图
    bool isMap(const MapID& mapId)const;
    // 获取地图
    AutoGameMap  getMap(const MapID& mapId) const;

    // 添加角色到特定地图
    void addRoleToMap(const MapID& mapId, const AutoRole role);

    // 删除角色
    void deleteRoleWithMap(const MapID& mapId, Role& role);
    void deleteRole(Role& role);

    // 移动角色
    void moveRoleWithMap(const MapID& mapId, Role& role, const Location& newLocation);
    void moveRole(Role& role, const Location& newLocation);

    // 判断该坐标是否有角色
    bool isRole(const MapID& mapId, const Location& location) const;

    // 获取该位置的对象
    AutoRole getRole(const MapID& mapId, const Location& location) const;

    // 随机生成角色
    void randomCreateRole(const MapID& mapId,Role& role);

    // 更新关卡逻辑
    void update(float deltaTime);

private:
    LevelMaps _maps;
    LevelID _levelID;//关卡标识符
};
