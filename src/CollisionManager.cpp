#include "CollisionManager.h"
#include "PortalManager.h"
#include "Log.h"

CollisionManager::CollisionManager(AutoGameManager gameManager)
	:_gameManager(gameManager)
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::RebindGameManager(AutoGameManager gameManager)
{
	_gameManager = gameManager;
}

bool CollisionManager::CollisionDetection(AutoGameObject obj, const Location& location, GameMap& map,GameLevel& level)
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

bool CollisionManager::CanItMoveAfterCollision(AutoGameObject obj,const Location& location, GameMap& map,GameLevel& level)
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
		CollisionWithThePortal(obj, location, map, level);
		ret = false;
		break;
	case ObjectType::GRASS:
		ret = true;
		break;
	default:
		break;
	}
	return ret;
}

void CollisionManager::CollisionWithThePortal(AutoGameObject obj, const Location& location, GameMap& map, GameLevel& level)
{
	PortalInfo portal= PORTAL_MANAGER.GetPortalInfo({
		level.GetID(),map.GetID(),location
		});
	PortalKeyEqual equal;
	if (!equal(portal,PORTAL_MANAGER.invalidPortalInfo)) {
		//如果传送门有注册
		LevelID tolevel= get<0>(portal);
		MapID toMap = get<1>(portal);
		Location toLocation = get<2>(portal);
		
		//添加到新位置
		_gameManager->GetNonConstLevel(tolevel)
					->GetNonConstMap(toMap)
					->AddGameObject(obj, toLocation);
		//删除旧位置
		map.RemoveGameObject(_gameManager->GetCurrentLocation());
		//设置玩家当前信息
		_gameManager->SetPlayerLevel(_gameManager->GetNonConstLevel(tolevel));
		_gameManager->SetPlayerMap(_gameManager->GetNonConstLevel(tolevel)->GetNonConstMap(toMap));
		_gameManager->SetPlayerLocation(toLocation);
		_gameManager->GetPlayer()->GetObjectSelf()->SetLocation(toLocation);
		LOG_INFO("传送至:"+tolevel+toMap+toLocation.ToString());
	}
	else {
		LOG_ERROR("尝试碰撞不存在的传送点");
	}
}
