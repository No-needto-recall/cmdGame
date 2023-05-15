#pragma once

#include <memory>
#include "Role.h"
#include "Behavior.h"
#include "GameMap.h"


using std::shared_ptr;
using std::unique_ptr;


namespace CreatRole {
	AutoRole creatPlayerRoleFromConfig(AutoGameMap gamemap);
	AutoRole creatPokemonFromConfig(const Location&);
};//end of CreatRole


namespace CreatBehavior {
	AutoBehavior creatPlayerBehaviorFromConfig(AutoWeakRole role );
	AutoBehavior creatPokemonFromConfig(AutoWeakRole role);

};//end of CreatBehavior
