#include "GameManager.h"
#include "GamePlayer.h"
#include "Log.h"

//静态数据成员初始化

Location GameManager::defaultLocation = { -1, -1 };


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
	if (_player->GetMap()) {
		_player->GetNonConstMap()->AddGameObject(obj, loc);
	}
	else {
		LOG_ERROR("当前地图为nullptr");
	}
}

void GameManager::RemoveObjectCurrentMap(const Location& loc)
{
	if (_player->GetMap()) {
		_player->GetNonConstMap()->RemoveGameObject(loc);
	}
	else {
		LOG_ERROR("当前地图为nullptr");
	}
}

void GameManager::MoveObjectCurrentMap(const Location& from, const Location& to)
{
	if (_player->GetMap()) {
		_player->GetNonConstMap()->MoveGameObject(from, to);
	}
	else {
		LOG_ERROR("当前地图为nullptr");
	}
}

void GameManager::ReplaceGameObjectCurrentMap(AutoGameObject obj, const Location& loc)
{
	if (_player->GetMap()) {
		_player->GetNonConstMap()->ReplaceGameObject(obj, loc);
	}
	else {
		LOG_ERROR("当前地图为nullptr");
	}
}

void GameManager::AddObjectCurrentLevel(const MapID& mapId, const Location& loc, AutoGameObject obj)
{
	if (_player->GetLevel()) {
		_player->GetNonConstLevel()->AddObjectWith(mapId, loc, obj);
	}
	else {
		LOG_ERROR("当前关卡为nullptr");
	}
}

void GameManager::RemoveObjectCurrentLevel(const MapID& mapId, const Location& loc)
{
	if (_player->GetLevel()) {
		_player->GetNonConstLevel()->RemoveObjectWith(mapId, loc);
	}
	else {
		LOG_ERROR("当前关卡为nullptr");
	}
}

void GameManager::MoveObjectCurrentLevel(const MapID& mapId, const Location& from, const Location& to)
{
	if (_player->GetLevel()) {
		_player->GetNonConstLevel()->MoveObjectWith(mapId, from, to);
	}
	else {
		LOG_ERROR("当前关卡为nullptr");
	}
}

void GameManager::ReplaceGameObjectCurrentLevel(const MapID& mapId, AutoGameObject obj, const Location& loc)
{
	if (_player->GetLevel()) {
		_player->GetNonConstLevel()->ReplaceGameObject(mapId, obj, loc);
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

void GameManager::CurrentMoveToOtherMap(const LevelID& toLevelId, const MapID& toMapID, const Location to)
{
	if (GetCurrentLevel()) {
		if (GetCurrentMap()) {
			auto to_level = _levels.find(toLevelId);
			if (to_level != _levels.end()) {
				//在另一个关卡中添加
				to_level->second->AddObjectWith(toMapID, to,
					GetNonConstCurrentMap()->GetGameObject(GetCurrentLocation())
					);
				//删除原来的
				GetNonConstCurrentMap()->RemoveGameObject(GetCurrentLocation());
				//设置玩家当前关卡、地图、位置
				SetPlayerLevel(to_level->second.get());
				SetPlayerMap(to_level->second->GetNonConstMap(toMapID));
				SetPlayerLocation(to);
			}
			else {
				LOG_ERROR("不存在关卡:" +toLevelId+"移动object失败");
			}
		}
		else {
			LOG_ERROR("当前地图为nullptr");
		}
	}
	else {
		LOG_ERROR("当前关卡为nullptr");
	}
}


GameManager::GameManager(AutoGamePlayer player)
	:_player(player)
{
}

GameManager::~GameManager()
{
}

const GameLevel* GameManager::GetCurrentLevel() const
{
	if (_player) {
		return _player->GetLevel();
	}
	else {
		LOG_ERROR("绑定的玩家为nullptr");
		return nullptr;
	}
}

GameLevel* GameManager::GetNonConstCurrentLevel()
{
	if (_player) {
		return _player->GetNonConstLevel();
	}
	else {
		LOG_ERROR("绑定的玩家为nullptr");
		return nullptr;
	}
}

void GameManager::SetPlayerLevel(GameLevel* newLevel)
{
	if (newLevel) {
		_player->SetLevel(newLevel);
	}
	else {
		LOG_ERROR("试图将当前关卡绑定为nullptr");
	}
}

const GameMap* GameManager::GetCurrentMap() const
{
	if (_player) {
		return _player->GetMap();
	}
	else {
		LOG_ERROR("绑定的玩家为nullptr");
		return nullptr;
	}
}

GameMap* GameManager::GetNonConstCurrentMap()
{
	if (_player) {
		return _player->GetNonConstMap();
	}
	else {
		LOG_ERROR("绑定的玩家为nullptr");
		return nullptr;
	}
}

void GameManager::SetPlayerMap(GameMap* newGameMap)
{
	if (newGameMap) {
		_player->SetMap(newGameMap);
	}
	else {
		LOG_ERROR("试图将当前地图绑定为nullptr");
	}
}

const Location& GameManager::GetCurrentLocation() const
{
	if (_player) {
		return _player->GetLocation();
	}
	else {
		LOG_ERROR("绑定的玩家为nullptr,将获取defaultLocation");
		return defaultLocation;
	}
}

Location& GameManager::GetNonConstCurrentLocation() 
{
	if (_player) {
		return _player->GetNonConstLocation();
	}
	else {
		LOG_ERROR("绑定的玩家为nullptr,将获取defaultLocation");
		return defaultLocation;
	}
}

void GameManager::SetPlayerLocation(const Location& newLocation)
{
	_player->SetLocation(newLocation);
}

void GameManager::BindPlayer(AutoGamePlayer player)
{
	if (player) {
		_player = player;
	}
	else {
		LOG_ERROR("尝试绑定的玩家为nullptr");
	}
}

const GamePlayer* GameManager::GetPlayer() const
{
	return _player.get();
}

GamePlayer* GameManager::GetNonConstPlayer()
{
	return _player.get();
}

void GameManager::AddLevel(AutoGameLevel newLevel)
{
	LevelID tmpID = newLevel->GetID();
	auto ret = _levels.insert({tmpID,std::move(newLevel)});
	if (ret.second) {
		LOG_INFO("添加关卡:"+tmpID+" 成功");
	}
	else {
		LOG_ERROR("添加关卡:"+tmpID+" 失败(重复)");
	}
}

void GameManager::DelLevel(const LevelID& id)
{
	auto ret = _levels.erase(id);
	if (ret) {
		LOG_INFO("删除关卡:"+id+" 成功");
	}
	else {
		LOG_ERROR("删除关卡:"+id+" 成功");
	}
}

const GameLevel* GameManager::GetLevel(const LevelID& id)
{
	auto level = _levels.find(id);
	if (level != _levels.end()) {
		return level->second.get();
	}
	else {
		LOG_ERROR("获取不存在level:" + id);
		return nullptr;
	}
}

GameLevel* GameManager::GetNonConstLevel(const LevelID& id)
{
	auto level = _levels.find(id);
	if (level != _levels.end()) {
		return level->second.get();
	}
	else {
		LOG_ERROR("获取不存在level:" + id);
		return nullptr;
	}
}
