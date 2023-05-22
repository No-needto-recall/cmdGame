#include "GamePlayer.h"
#include "GameObject.h"
#include "GameMap.h"
#include "CollisionManager.h"
#include "Log.h"


GamePlayer::GamePlayer(const string& name, GameLevel* levelNow, GameMap* mapNow, const Location& location, AutoGameObject selfObject, AutoCollisionManager collision)
	:_name(name),_levelNow(levelNow),_mapNow(mapNow),_locationNow(location)
	,_myObject(selfObject),_myCollision(std::move(collision))
{
}

const string& GamePlayer::GetName() const
{
	return _name;
}

void GamePlayer::SetName(const string& name)
{
	_name = name;
}

const GameLevel* GamePlayer::GetLevel() const
{
	if (_levelNow) {
		return _levelNow;
	}
	else {
		LOG_ERROR("当前关卡指针为nullptr");
		return nullptr;
	}
}

const GameMap* GamePlayer::GetMap() const
{
	if (_mapNow) {
		return _mapNow;
	}
	else {
		LOG_ERROR("当前地图指针为nullptr");
		return nullptr;
	}
}

const Location& GamePlayer::GetLocation() const
{
	return _locationNow;
}

GameLevel* GamePlayer::GetNonConstLevel()
{
	if (_levelNow) {
		return _levelNow;
	}
	else {
		LOG_ERROR("当前关卡指针为nullptr");
		return nullptr;
	}
}

GameMap* GamePlayer::GetNonConstMap()
{
	if (_mapNow) {
		return _mapNow;
	}
	else {
		LOG_ERROR("当前地图指针为nullptr");
		return nullptr;
	}
}

Location& GamePlayer::GetNonConstLocation()
{
	return _locationNow;
}

void GamePlayer::SetLevel(GameLevel* level)
{
	if (level) {
		_levelNow = level;
	}
	else {
		LOG_ERROR("不能将当前关卡指针设为nullptr");
	}
}

void GamePlayer::SetMap(GameMap* map)
{
	if (map) {
		_mapNow = map;
	}
	else {
		LOG_ERROR("不能将当前地图指针设为nullptr");
	}
}

void GamePlayer::SetLocation(const Location& location)
{
	_locationNow = location;
}

AutoGameObject GamePlayer::GetObjectSelf() const
{
	return _myObject;
}

AutoGameObject GamePlayer::GetObjectWithLocation(const Location& location) const
{
	return _mapNow->GetGameObject(location);
}

void GamePlayer::MoveToLocation(const Location& newLocation)
{
	//如果新坐标不在地图内,则无需移动
	if (!_mapNow->InGameMap(newLocation)) {
		return;
	}
	//判断是否需要碰撞处理
	if (_myCollision->CollisionDetection(_myObject,newLocation,*_mapNow,*_levelNow)) {
		//判断碰撞处理后不能移动
		if (!_myCollision->CanItMoveAfterCollision(_myObject,newLocation, *_mapNow,*_levelNow)) {
			return;
		}
	}
	_mapNow->MoveGameObject(_locationNow, newLocation);
	LOG_INFO(_name + "从" + _locationNow.ToString() + "移动到" + newLocation.ToString());
	_locationNow = newLocation;
	_myObject->SetLocation(newLocation);
}

void GamePlayer::UpMove()
{
	Location newLocation = _myObject->GetLocation();
	newLocation.y -= 1;
	MoveToLocation(newLocation);
}

void GamePlayer::DownMove()
{
	Location newLocation = _myObject->GetLocation();
	newLocation.y += 1;
	MoveToLocation(newLocation);
}

void GamePlayer::LeftMove()
{
	Location newLocation = _myObject->GetLocation();
	newLocation.x -= 1;
	MoveToLocation(newLocation);
}

void GamePlayer::RightMove()
{
	Location newLocation = _myObject->GetLocation();
	newLocation.x += 1;
	MoveToLocation(newLocation);
}

