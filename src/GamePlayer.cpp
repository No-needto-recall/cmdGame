#include "GamePlayer.h"
#include "GameObject.h"
#include "GameMap.h"
#include "CollisionManager.h"
#include "Log.h"


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
	//判断是否需要碰撞处理
	if (_myCollision->CollisionDetection(newLocation,*_mapNow)) {
		//判断碰撞处理后能否移动
		if (_myCollision->CollisionDetection(newLocation, *_mapNow)) {
			//让map移动对应位置的
			_mapNow->MoveGameObject(_myObject->GetLocation(), newLocation);
		}
	}
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

