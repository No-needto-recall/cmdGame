#include "Level.h"
#include "Log.h"
#include "GameMap.h"
#include "Role.h"

void Level::addMap(const MapID& mapId, const AutoGameMap map)
{
	_maps.insert({mapId,map});
	LOG_INFO("添加"+mapId+" 地图到 "+ _levelID+" 关卡");
}

void Level::removeMap(const MapID& mapId)
{
	auto ret = _maps.erase(mapId);
	if (ret) {
		LOG_INFO("地图："+mapId+" 从关卡 "+
				 _levelID +" 中移除(" + to_string(ret)+")");
	}
	else {
		LOG_ERROR("地图："+mapId+" 不存在于关卡 " +
				_levelID +" ,移除失败");
	}
}

bool Level::isMap(const MapID& mapId) const
{
	return _maps.count(mapId) > 0;
}

AutoGameMap Level::getMap(const MapID& mapId) const
{
	auto search = _maps.find(mapId);
	if (search != _maps.end()) {
		return search->second;
	}
	else {
		LOG_ERROR("尝试在关卡："+_levelID + 
				  " 中，获取不存在的地图："+mapId);
		::exit(1);
	}
}

void Level::addRoleToMap(const MapID& mapId, const AutoRole role)
{
	if (isMap(mapId)) {
		getMap(mapId)->addRole(role);
	}
	else {
		LOG_ERROR("尝试在关卡 " + _levelID + " 的不存在的地图："+
				 mapId + "中添加角色");
		::exit(1);
	}
}

void Level::deleteRoleWithMap(const MapID& mapId, Role& role)
{
	getMap(mapId)->deleteRole(role);
}

void Level::deleteRole(Role& role)
{
	role.getGameMap()->deleteRole(role);
}

void Level::moveRoleWithMap(const MapID& mapId, Role& role, const Location& newLocation)
{
	getMap(mapId)->moveRole(role, newLocation);
}

void Level::moveRole(Role& role, const Location& newLocation)
{
	role.getGameMap()->moveRole(role,newLocation);
}

bool Level::isRole(const MapID& mapId, const Location& location) const
{
	return getMap(mapId)->isRole(location);
}

AutoRole Level::getRole(const MapID& mapId, const Location& location) const
{
	return getMap(mapId)->getRole(location);
}

