#pragma once

#include <memory>
#include "Role.h"
#include "Behavior.h"
#include "GameMap.h"


using std::shared_ptr;
using std::unique_ptr;


namespace CreatRoleFromConfig {
	//创建不带地图绑定的配置玩家
	AutoRole PlayerRoleWithOutMap();
	AutoRole PlayerRoleWithOutMap(AutoGameMap gamemap);

	//创建不带地图绑定的配置宝可梦
	//宝可梦的创建需要附带位置信息
	AutoRole PokemonRoleWithOutMap(AutoGameMap gamemap);
};//end of CreatRole


namespace CreatBehavior {
	AutoBehavior creatPlayerBehaviorFromConfig(AutoWeakRole role );
	AutoBehavior creatPokemonFromConfig(AutoWeakRole role);

};//end of CreatBehavior
