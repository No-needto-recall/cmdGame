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
		   const Location& location,
			GameMap& gameMap)
	:BasicRole(location),_attribute(attribute)
	,_gameMap(gameMap)
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

const unique_ptr<Behavior>& Role::getBehavior() const
{
	return _behavior;
}

void Role::setBehavior(unique_ptr<Behavior> behavior)
{
	_behavior = std::move(behavior);
}

void Role::bindGameMap(GameMap& gamemap)
{
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
	//����
	other.collideWithPlayer(*this);
}

void PlayerRole::collideWithPlayer(Role& other)
{
	//��Һ���ҷ�����ײ

}

void PlayerRole::collideWithPokemon(Role&)
{
	//�����κ���ҷ�����ײ
}

void PokemonRole::collide(Role& other)
{
	//����
	other.collideWithPokemon(*this);
}

void PokemonRole::collideWithPlayer(Role& player)
{
	//��Һͱ����η�����ײ
	LOG_INFO(
		player.getAttribute()._name +" �� "+
		this->getAttribute()._name+" ������ײ"
	);

	//����ս��
	while (1) {
		player.getBehavior()->attack(*this);
		if (this->getAttribute().isAlive()) {

			this->getBehavior()->attack(player);

			if (player.getAttribute().isAlive()) {
				continue;
			}
			else {
				player.getBehavior()->death(player._gameMap);
				break;
			}
		}
		else {
			this->getBehavior()->death(this->_gameMap);
			break;
		}
	}

	return;
}

void PokemonRole::collideWithPokemon(Role&)
{
	//�����κͱ����η�����ײ
}
