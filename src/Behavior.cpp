#include "Behavior.h"
#include "Role.h"
#include "GameMap.h"
#include "Log.h"

Behavior::Behavior(Role& myself)
	:_mySelf(myself)
{}

/*
  ×ø±êÑÝÊ¾

  0----> x
  |
  |
  V
  y

 */


 //PlayerBehavior
void PlayerBehavior::upMove(GameMap& gameMap) {
	gameMap.moveRole(_mySelf, 
		{ _mySelf.getLocation()._x,_mySelf.getLocation()._y - 1 });
}

void PlayerBehavior::downMove(GameMap& gameMap)
{
	gameMap.moveRole(_mySelf, 
		{ _mySelf.getLocation()._x,_mySelf.getLocation()._y + 1 });
}

void PlayerBehavior::leftMove(GameMap& gameMap)
{
	gameMap.moveRole(_mySelf, 
		{ _mySelf.getLocation()._x - 1,_mySelf.getLocation()._y });
}

void PlayerBehavior::rightMove(GameMap& gameMap)
{
	gameMap.moveRole(_mySelf, 
		{ _mySelf.getLocation()._x + 1,_mySelf.getLocation()._y });
}

void PlayerBehavior::attack(Role& other)
{
	//¼òµ¥µÄ¹¥»÷¼õÈ¥·ÀÓùÁ¦Âß¼­
	int number = _mySelf.getAttribute()._attack - other.getAttribute()._defense;
	number = number < 0 ? 0 : number;
	other.getAttribute()._health -= number;
}

void PlayerBehavior::death(GameMap& gameMap)
{
	LOG_INFO(this->_mySelf.getAttribute()._name + "ËÀÍö");
	gameMap.deleteRole(this->_mySelf);
}

//PokemonBehavior
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

void PokemonBehavior::attack(Role& other)
{
	//¼òµ¥µÄ¹¥»÷¼õÈ¥·ÀÓùÁ¦Âß¼­
	int number = _mySelf.getAttribute()._attack - other.getAttribute()._defense;
	number = number < 0 ? 0 : number;
	other.getAttribute()._health -= number;
}

void PokemonBehavior::death(GameMap& gameMap)
{
	LOG_INFO(this->_mySelf.getAttribute()._name + "ËÀÍö");
	gameMap.deleteRole(this->_mySelf);
}

