// Actor.cpp
#include "Actor.h"

Actor::Actor(int hp, int mp, int attack, int defense, int x, int y, Type type, const string& name)
    : _hp(hp),
    _mp(mp),
    _attackPower(attack),
    _defensePower(defense),
    _x(x),
    _y(y),
    _type(type),
    _name(name),
    _gMap(nullptr)
{
}

Actor::~Actor() {
}

int Actor::getX() const {
    return _x;
}

int Actor::getY() const {
    return _y;
}

void Actor::setX(const int& x) {
    _x = x;
}

void Actor::setY(const int& y) {
    _y = y;
}

string Actor::getName() const {
    return _name;
}

void Actor::setName(const string& str) {
    _name = str;
}

Type Actor::getType() const {
    return _type;
}

bool Actor::isAlive() {
    return _hp > 0;
}

bool Actor::isDeath() {
    return _hp <= 0;
}

void Actor::AD_attack(Actor& target) {
    int injury = this->_attackPower > target._defensePower ? this->_attackPower - target._defensePower : 0;
    target._hp -= injury;
}

string Actor::getPosition() {
    return to_string(_x) + "," + to_string(_y);
}

void Actor::bindMap(GameMap* gMap) {
    _gMap = gMap;
}

GameMap* Actor::getMap(){
    return _gMap;
}

void Actor::left() {
    _gMap->moveActor(this, _x - 1, _y);
}

void Actor::right() {
    _gMap->moveActor(this, _x + 1, _y);
}

void Actor::up() {
    _gMap->moveActor(this, _x, _y - 1);
}

void Actor::down() {
    _gMap->moveActor(this, _x, _y + 1);
}
