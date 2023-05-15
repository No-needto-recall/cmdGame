#include "CreatFromConfig.h"
#include "Behavior.h"
#include "config.h"
#include "Log.h"

AutoRole CreatRole::creatPlayerRoleFromConfig(AutoGameMap gamemap)
{
	AutoRole role(new PlayerRole(
		{
		Config::instance().getConfigData().role.player.name,
		Config::instance().getConfigData().role.player.health,
		Config::instance().getConfigData().role.player.mana,
		Config::instance().getConfigData().role.player.attack,
		Config::instance().getConfigData().role.player.defense,
		Config::instance().getConfigData().role.player.icon
		},
		{
		Config::instance().getConfigData().role.player.spawnX,
		Config::instance().getConfigData().role.player.spawnY
		}
		));
		role->setBehavior(AutoBehavior(new PlayerBehavior(role)));
		role->setGameMap(gamemap);
		return role;
}

AutoRole CreatRole::creatPokemonFromConfig(const Location& location)
{
	return AutoRole(new PokemonRole(
		{
		Config::instance().getConfigData().role.pokemon.name,
		Config::instance().getConfigData().role.pokemon.health,
		Config::instance().getConfigData().role.pokemon.mana,
		Config::instance().getConfigData().role.pokemon.attack,
		Config::instance().getConfigData().role.pokemon.defense,
		Config::instance().getConfigData().role.pokemon.icon,
		},
		location
	));
}

AutoBehavior CreatBehavior::creatPlayerBehaviorFromConfig(AutoWeakRole role)
{
	return AutoBehavior( new 
		PlayerBehavior(role)
	);
}

AutoBehavior CreatBehavior::creatPokemonFromConfig(AutoWeakRole role)
{
	return AutoBehavior( new 
	PokemonBehavior(role)
	);
}
