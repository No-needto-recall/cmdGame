#include "GameManager.h"
#include "Log.h"

AutoGameObject GameManager::GetObjectWith(const LevelID& levelId, const MapID& mapID, const Location& loc) const
{
	auto ret = _levels.find(levelId);
	if (ret != _levels.end()) {
		return	ret->second->GetObjectWith(mapID, loc);
	}
	else {
		LOG_ERROR("不存在关卡:" + levelId +"添加object失败");
		return nullptr;
	}
}

void GameManager::AddObjectCurrentMap(const Location& loc, AutoGameObject obj)
{
	if (_currentMap) {
		_currentMap->AddGameObject(obj, loc);
	}
	else {
		LOG_ERROR("当前地图为nullptr");
	}
}

void GameManager::RemoveObjectCurrentMap(const Location& loc)
{
	if (_currentMap) {
		_currentMap->RemoveGameObject(loc);
	}
	else {
		LOG_ERROR("当前地图为nullptr");
	}
}

void GameManager::MoveObjectCurrentMap(const Location& from, const Location& to)
{
	if (_currentMap) {
		_currentMap->MoveGameObject(from, to);
	}
	else {
		LOG_ERROR("当前地图为nullptr");
	}
}

void GameManager::ReplaceGameObjectCurrentMap(AutoGameObject obj, const Location& loc)
{
	if (_currentMap) {
		_currentMap->ReplaceGameObject(obj,loc);
	}
	else {
		LOG_ERROR("当前地图为nullptr");
	}
}

void GameManager::AddObjectCurrentLevel(const MapID& mapId, const Location& loc, AutoGameObject obj)
{
	if (_currentLevel) {
		_currentLevel->AddObjectWith(mapId, loc, obj);
	}
	else {
		LOG_ERROR("当前关卡为nullptr");
	}
}

void GameManager::RemoveObjectCurrentLevel(const MapID& mapId, const Location& loc)
{
	if (_currentLevel) {
		_currentLevel->RemoveObjectWith(mapId, loc);
	}
	else {
		LOG_ERROR("当前关卡为nullptr");
	}
}

void GameManager::MoveObjectCurrentLevel(const MapID& mapId, const Location& from, const Location& to)
{
	if (_currentLevel) {
		_currentLevel->MoveObjectWith(mapId, from, to);
	}
	else {
		LOG_ERROR("当前关卡为nullptr");
	}
}

void GameManager::ReplaceGameObjectCurrentLevel(const MapID& mapId, AutoGameObject obj, const Location& loc)
{
	if (_currentLevel) {
		_currentLevel->ReplaceGameObject(mapId, obj, loc);
	}
	else {
		LOG_ERROR("当前关卡为nullptr");
	}
}

void GameManager::AddObject(const LevelID& levelId, const MapID& mapId, const Location& loc, AutoGameObject obj)
{
	auto ret = _levels.find(levelId);
	if (ret != _levels.end()) {
		ret->second->AddObjectWith(mapId, loc, obj);
	}
	else {
		LOG_ERROR("不存在关卡:" + levelId +"添加object失败");
	}
}

void GameManager::RemoveObject(const LevelID& levelId, const MapID& mapId, const Location& loc)
{
	auto ret = _levels.find(levelId);
	if (ret != _levels.end()) {
		ret->second->RemoveObjectWith(mapId, loc);
	}
	else {
		LOG_ERROR("不存在关卡:" + levelId +"删除object失败");
	}
}

void GameManager::MoveObject(const LevelID& levelId, const MapID& mapId, const Location& from, const Location& to)
{
	auto ret = _levels.find(levelId);
	if (ret != _levels.end()) {
		ret->second->MoveObjectWith(mapId, from, to);
	}
	else {
		LOG_ERROR("不存在关卡:" + levelId +"移动object失败");
	}
}

void GameManager::ReplaceGameObject(const LevelID& levelId, const MapID& mapId, AutoGameObject obj, const Location& loc)
{
	auto ret = _levels.find(levelId);
	if (ret != _levels.end()) {
		ret->second->ReplaceGameObject(mapId, obj, loc);
	}
	else {
		LOG_ERROR("不存在关卡:" + levelId +"替换object失败");
	}
}

void GameManager::MoveObjectMapToMap(const LevelID& fromLevelId, const MapID& fromMapId, const LevelID& toLevelId, const MapID& toMapId, const Location& from, const Location& to)
{
	auto from_level= _levels.find(fromLevelId);
	if (from_level!= _levels.end()) {
		auto to_level = _levels.find(toLevelId);
		if (to_level != _levels.end()) {
			//在另一个关卡中添加
			to_level->second->AddObjectWith(toMapId, to,
				from_level->second->GetObjectWith(fromMapId, from));
			//删除原来的
			from_level->second->RemoveObjectWith(fromMapId, from);
		}
	}
	else {
		LOG_ERROR("不存在关卡:" +fromLevelId  +"移动object失败");
	}
}

