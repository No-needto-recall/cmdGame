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



class Level {
public:
    Level();
    ~Level();

    // 添加地图到关卡
    void addMap(const MapID& mapId, const AutoGameMap& map);

    // 删除地图
    void removeMap(const MapID& mapId);

    // 获取地图
    AutoGameMap  getMap(const MapID& mapId) const;

    // 添加角色到特定地图
    void addRole(const MapID& mapId, const AutoRole& role);

    // 删除角色
    void deleteRole(const MapID& mapId, const Role& role);

    // 移动角色
    void moveRole(const MapID& mapId, const Role& role, const Location& newLocation);

    // 判断该坐标是否有角色
    bool isRole(const MapID& mapId, const Location& location) const;

    // 获取该位置的对象
    AutoRole getRole(const MapID& mapId, const Location& location) const;

    // 随机生成角色
    void randomCreateRole(const MapID& mapId);

    // 更新关卡逻辑
    void update(float deltaTime);

private:
    LevelMaps _maps;
};
