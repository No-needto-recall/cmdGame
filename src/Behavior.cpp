#include "Behavior.h"
#include "Role.h"
#include "GameMap.h"

void PlayerBehavior::upMove(GameMap& gameMap){
	
}

void PlayerBehavior::downMove(GameMap& gameMap)
{
}

void PlayerBehavior::leftMove(GameMap& gameMap)
{
}

void PlayerBehavior::rightMove(GameMap& gameMap)
{
}

void PlayerBehavior::attack(Role&)
{
}

void PlayerBehavior::death(GameMap& gameMap)
{
}

void PlayerBehavior::collide(Behavior& other)
{
	other.collideWithPlayer(*this);
}

void PlayerBehavior::collideWithPlayer(PlayerBehavior&)
{
}

void PlayerBehavior::collideWithPokemon(PokemonBehavior&)
{
}

void PokemonBehavior::upMove(GameMap& gameMap)
{
}

void PokemonBehavior::downMove(GameMap& gameMap)
{
}

void PokemonBehavior::leftMove(GameMap& gameMap)
{
}

void PokemonBehavior::rightMove(GameMap& gameMap)
{
}

void PokemonBehavior::attack(Role&)
{
}

void PokemonBehavior::death(GameMap& gameMap)
{
}

void PokemonBehavior::collide(Behavior& other)
{
	other.collideWithPokemon(*this);
}

void PokemonBehavior::collideWithPlayer(PlayerBehavior&)
{
}

void PokemonBehavior::collideWithPokemon(PokemonBehavior&)
{
}
