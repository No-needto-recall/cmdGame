#include "CreatFromConfig.h"
#include "Behavior.h"
#include "config.h"
#include "Log.h"

AutoRole CreatRoleFromConfig::PlayerRoleWithOutMap()
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
		return role;

}

AutoRole CreatRoleFromConfig::PlayerRoleWithOutMap(AutoGameMap gamemap)
{
		AutoRole role = PlayerRoleWithOutMap();
		role->setGameMap(gamemap);
		return role;
}


AutoRole CreatRoleFromConfig::PokemonRoleWithOutMap(AutoGameMap gamemap)
{
	AutoRole role(new PokemonRole(
		{
		Config::instance().getConfigData().role.pokemon.name,
		Config::instance().getConfigData().role.pokemon.health,
		Config::instance().getConfigData().role.pokemon.mana,
		Config::instance().getConfigData().role.pokemon.attack,
		Config::instance().getConfigData().role.pokemon.defense,
		Config::instance().getConfigData().role.pokemon.icon,
		},
		gamemap->randomCollisionFreePosition()
	));
	role->setBehavior(AutoBehavior(new PokemonBehavior(role)));
	role->setGameMap(gamemap);
	return role;
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
