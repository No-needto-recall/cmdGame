#include "Role.h"
#include "Behavior.h"
#include "Log.h"


BasicRole::BasicRole(const Location & location)
	:_location(location)
{}

BasicRole::~BasicRole()
{}

const Location& BasicRole::getLocation()const {
	return _location;
}

Location& BasicRole::getLocation() {
	return _location;
}

Role::Role(const Attribute& attribute,
		   const Location& location)
	:BasicRole(location),_attribute(attribute)
{}

Role::Role(const Attribute & attribute, const Location & location, AutoBehavior behavior)
	:BasicRole(location),_attribute(attribute)
	,_behavior(std::move(behavior))
{
}

Role::Role(const Attribute& attribute, const Location& location, AutoGameMap gamemap)
	:BasicRole(location),_attribute(attribute)
	,_gameMap(gamemap)
{
}

Role::Role(const Attribute& attribute, const Location& location, AutoBehavior behavior, AutoGameMap gamemap)
	:BasicRole(location),_attribute(attribute)
	,_behavior(std::move(behavior))
	,_gameMap(gamemap)
{
}


Role::~Role()
{}

const Attribute& Role::getAttribute() const
{
	return _attribute;
}

Attribute& Role::getAttribute()
{
	return _attribute;
}

bool Role::isAlive() const
{
	return _attribute.isAlive();
}

bool Role::isDeath() const
{
	return _attribute.isDeath();
}


void Role::setBehavior(AutoBehavior behavior)
{
	_behavior = std::move(behavior);
}

//上移
void Role::upMove()
{
	_behavior->upMove(*_gameMap);
}
//下移
void Role::downMove()
{
	_behavior->downMove(*_gameMap);
}
//左移
void Role::leftMove()
{
	_behavior->leftMove(*_gameMap);
}
//右移
void Role::rightMove()
{
	_behavior->rightMove(*_gameMap);
}

void Role::death()
{
	_behavior->death(*_gameMap);
}

void Role::attack(Role& target)
{
	_behavior->attack(target);
}

void Role::setGameMap(AutoGameMap gamemap)
{
	_gameMap = gamemap;
}

AutoGameMap& Role::getGameMap()
{
	return _gameMap;
}

bool Attribute::isAlive() const
{
	return _health>0;
}

bool Attribute::isDeath() const
{
	return _health<=0;
}

string Location::toString() const
{
	string tmp = "(" + 
				std::to_string(_x) + 
				"," +
				std::to_string(_y) +
				")";
	return tmp;
}

void PlayerRole::collide(Role& other)
{
	//第一次分派
	other.collideWithPlayer(*this);
}

void PlayerRole::collideWithPlayer(Role& other)
{
	//玩家碰撞到玩家

}

void PlayerRole::collideWithPokemon(Role&)
{
	//宝可梦碰撞到玩家
}

void PokemonRole::collide(Role& other)
{
	//第一次分派
	other.collideWithPokemon(*this);
}

void PokemonRole::collideWithPlayer(Role& player)
{
	//玩家碰撞到宝可梦
	LOG_INFO(
		player.getAttribute()._name +" 与 "+
		this->getAttribute()._name+" 发生战斗 "
	);

	//简单的战斗逻辑
	while (1) {
		player.attack(*this);
		if (this->isAlive()) {

			this->attack(player);

			if (player.isAlive()) {
				continue;
			}
			else {
				player.death();
				break;
			}
		}
		else {
			this->death();
			break;
		}
	}

	return;
}

void PokemonRole::collideWithPokemon(Role&)
{
	//宝可梦碰撞到宝可梦
}
