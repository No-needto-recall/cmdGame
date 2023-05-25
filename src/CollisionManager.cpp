#include "CollisionManager.h"
#include "PortalManager.h"
#include "GameTool.h"
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
		CollisionWithTheGrass(obj, location, map, level);
		ret = false;
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
		//更新玩家当前信息
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

void CollisionManager::CollisionWithTheGrass(AutoGameObject obj, const Location& location, GameMap& map, GameLevel& level)
{
	//当碰撞到草丛的时候
	//先移动到草丛,(一定是在当前关卡的当前地图)
	_gameManager->GetNonConstPlayer()->RealMove(location);
	//roll点判断是否发生战斗
	if (GameTool::randomAtoB(1, 100) > 50) {
		LOG_INFO("触发战斗");
	//进入战斗循环
	//结束战斗循环
	}
	else {
		return;
	}
}
