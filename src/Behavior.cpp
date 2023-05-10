#include "Behavior.h"
#include "Role.h"
#include "GameMap.h"
#include "Log.h"

Behavior::Behavior(AutoWeakRole myself)
	:_mySelf(myself)
{}

bool Behavior::isExist()const {
	return !_mySelf.expired();
}

/*
  ������ʾ

  0-------> x
  |
  |
  V
  y

 */


 //PlayerBehavior
void PlayerBehavior::upMove(GameMap& gameMap) {
	auto mySelf = _mySelf.lock();
	if (mySelf) {
		gameMap.moveRole(*mySelf,
		{ mySelf->getLocation()._x,mySelf->getLocation()._y - 1 });
	}
	else {
		LOG_ERROR("playerBehavior�󶨵Ķ���������");
	}
}

void PlayerBehavior::downMove(GameMap& gameMap)
{
	auto mySelf = _mySelf.lock();
	if (mySelf) {
		gameMap.moveRole(*mySelf,
		{ mySelf->getLocation()._x,mySelf->getLocation()._y + 1 });
	}
	else {
		LOG_ERROR("playerBehavior�󶨵Ķ���������");
	}
}

void PlayerBehavior::leftMove(GameMap& gameMap)
{
	auto mySelf = _mySelf.lock();
	if (mySelf) {
		gameMap.moveRole(*mySelf,
			{ mySelf->getLocation()._x - 1,mySelf->getLocation()._y });
	}
	else {
		LOG_ERROR("playerBehavior�󶨵Ķ���������");
	}
}

void PlayerBehavior::rightMove(GameMap& gameMap)
{
	auto mySelf = _mySelf.lock();
	if (mySelf) {
		gameMap.moveRole(*mySelf,
			{ mySelf->getLocation()._x + 1,mySelf->getLocation()._y });
	}
	else {
		LOG_ERROR("playerBehavior�󶨵Ķ���������");
	}
}

void PlayerBehavior::attack(Role& other)
{
	auto mySelf = _mySelf.lock();
	if (mySelf) {
		//�򵥵Ĺ�����ȥ�������߼�
		int number = mySelf->getAttribute()._attack - other.getAttribute()._defense;
		number = number < 0 ? 0 : number;
		other.getAttribute()._health -= number;
	}
	else {
		LOG_ERROR("playerBehavior�󶨵Ķ���������");
	}

}

void PlayerBehavior::death(GameMap& gameMap)
{
	auto mySelf = _mySelf.lock();
	if (mySelf) {
		LOG_INFO(mySelf->getAttribute()._name + "����");
		gameMap.deleteRole(*mySelf);
	}
	else {
		LOG_ERROR("playerBehavior�󶨵Ķ���������");
	}
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
	//�򵥵Ĺ�����ȥ�������߼�
	auto mySelf = _mySelf.lock();
	if (mySelf) {
		int number = mySelf->getAttribute()._attack - other.getAttribute()._defense;
		number = number < 0 ? 0 : number;
		other.getAttribute()._health -= number;
	}
	else {
		LOG_ERROR("PokemonBehavior�󶨵Ķ���������");
	}
}

void PokemonBehavior::death(GameMap& gameMap)
{
	auto mySelf = _mySelf.lock();
	if (mySelf) {
		LOG_INFO(mySelf->getAttribute()._name + "����");
		gameMap.deleteRole(*mySelf);
	}
	else {
		LOG_ERROR("PokemonBehavior�󶨵Ķ���������");
	}
}

