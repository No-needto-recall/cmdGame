#include "CollisionManager.h"
#include "GameMap.h"

bool CollisionManager::CollisionDetection(const Location& location, GameMap& map)
{
	auto object = map.GetGameObject(location);
	auto type = object->GetType();
	bool ret = false;
	switch (type)
	{
	case ObjectType::PLAYER:
		break;
	case ObjectType::GROUND:
		break;
	case ObjectType::WALL:
		ret = true;
		break;
	case ObjectType::PORTAL:
		ret = true;
		break;
	case ObjectType::GRASS:
		ret = true;
		break;
	default:
		break;
	}
	return ret;
}

bool CollisionManager::CanItMoveAfterCollision(const Location& location, GameMap& map)
{
	auto object = map.GetGameObject(location);
	auto type = object->GetType();
	bool ret = false;
	switch (type)
	{
	case ObjectType::PLAYER:
		break;
	case ObjectType::GROUND:
		ret = true;
		break;
	case ObjectType::WALL:
		ret = false;
		break;
	case ObjectType::PORTAL:
		ret = true;
		break;
	case ObjectType::GRASS:
		ret = true;
		break;
	default:
		break;
	}
	return ret;
}
