#include "GameLevel.h"
#include "Log.h"

GameLevel::GameLevel(LevelID id)
	:_id(id)
{
}

GameLevel::~GameLevel()
{
}

const LevelID& GameLevel::GetID() const
{
	return _id;
}

void GameLevel::AddMap(AutoGameMap map)
{
	MapID tmpID = map->GetID();
	auto ret=_maps.insert({ tmpID,std::move(map)});
	if (ret.second) {
		LOG_INFO("关卡:"+_id+" 添加地图:"+tmpID+" 成功");
	}
	else {
		LOG_ERROR("关卡:"+_id+" 添加地图:"+tmpID+" 失败(重复)");
	}
}

void GameLevel::DelMap(const MapID& id)
{
	auto ret=_maps.erase(id);
	if (ret) {
		LOG_INFO("关卡:"+_id+" 移除地图:"+id+" 成功");
	}
	else {
		LOG_ERROR("关卡:"+_id+" 移除地图:"+id+" 失败(不存在)");
	}
}

const GameMap* GameLevel::GetMap(const MapID& id) const
{
	auto ret = _maps.find(id);
	if (ret != _maps.end()) {
		return ret->second.get();
	}
	else {
		LOG_ERROR("尝试获取不存在的地图:"+id);
		return nullptr;
	}
}

GameMap* GameLevel::GetNonConstMap(const MapID& id)
{
	auto ret = _maps.find(id);
	if (ret != _maps.end()) {
		return ret->second.get();
	}
	else {
		return nullptr;
	}
	
}

int GameLevel::GetMapRows(const MapID& id) const
{
	return GetMap(id)->GetRows();
}

int GameLevel::GetMapCols(const MapID& id) const
{
	return GetMap(id)->GetCols();
}

AutoGameObject GameLevel::GetObjectWith(const MapID& id, const Location& location) const
{
	auto ret = _maps.find(id);
	if (ret != _maps.end()) {
		return ret->second->GetGameObject(location);
	}
	else {
		LOG_ERROR("尝试获取不存在的地图:"+id);
		return nullptr;
	}
}

void GameLevel::AddObjectWith(const MapID& id, const Location& location, AutoGameObject object)
{
	auto ret = _maps.find(id);
	if (ret != _maps.end()) {
		ret->second->AddGameObject(object,location);
	}
	else {
		LOG_ERROR("尝试在不存在的地图:"+id+"添加object");
	}
}

void GameLevel::RemoveObjectWith(const MapID& id, const Location& location)
{
	auto ret = _maps.find(id);
	if (ret != _maps.end()) {
		ret->second->RemoveGameObject(location);
	}
	else {
		LOG_ERROR("尝试在不存在的地图:"+id+"删除object");
	}
}

void GameLevel::MoveObjectWith(const MapID& id, const Location& from, const Location& to)
{
	auto ret = _maps.find(id);
	if (ret != _maps.end()) {
		ret->second->MoveGameObject(from,to);
	}
	else {
		LOG_ERROR("尝试在不存在的地图:" + id + "移动object");
	}
}

void GameLevel::ReplaceGameObject(const MapID& id, AutoGameObject object, const Location& location)
{
	auto ret = _maps.find(id);
	if (ret != _maps.end()) {
		ret->second->ReplaceGameObject(object,location);
	}
	else {
		LOG_ERROR("尝试在不存在的地图:" + id + "替换object");
	}
}

void GameLevel::MoveObjectMapToMap(const MapID& fromId, const MapID& toID, const Location& from, const Location& to)
{
	AddObjectWith(toID, to,GetObjectWith(fromId,from));
	RemoveObjectWith(fromId, from);
}


