#include "GamePlayer.h"
#include "GameObject.h"
#include "GameMap.h"
#include "CollisionManager.h"

GamePlayer::GamePlayer(const string& name)
	:_name(name)
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

