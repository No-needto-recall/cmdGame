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

const AutoBehavior& Role::getBehavior() const
{
	return _behavior;
}

void Role::setBehavior(AutoBehavior behavior)
{
	_behavior = std::move(behavior);
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
	//分派
	other.collideWithPlayer(*this);
}

void PlayerRole::collideWithPlayer(Role& other)
{
	//玩家和玩家发生碰撞

}

void PlayerRole::collideWithPokemon(Role&)
{
	//宝可梦和玩家发生碰撞
}

void PokemonRole::collide(Role& other)
{
	//分派
	other.collideWithPokemon(*this);
}

void PokemonRole::collideWithPlayer(Role& player)
{
	//玩家和宝可梦发生碰撞
	LOG_INFO(
		player.getAttribute()._name +" 和 "+
		this->getAttribute()._name+" 发生碰撞"
	);

	//发生战斗
	while (1) {
		player.getBehavior()->attack(*this);
		if (this->getAttribute().isAlive()) {

			this->getBehavior()->attack(player);

			if (player.getAttribute().isAlive()) {
				continue;
			}
			else {
				player.getBehavior()->death(*(player.getGameMap().get()));
				break;
			}
		}
		else {
			this->getBehavior()->death(*(this->getGameMap().get()));
			break;
		}
	}

	return;
}

void PokemonRole::collideWithPokemon(Role&)
{
	//宝可梦和宝可梦发生碰撞
}
