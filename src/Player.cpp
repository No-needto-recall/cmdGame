#include "Player.h"

void Player::left() {
	this->_gMap->moveActor(this, _x - 1, _y);
}

void Player::right() {
	this->_gMap->moveActor(this, _x + 1, _y);
}

void Player::up() {
	this->_gMap->moveActor(this, _x, _y - 1);
}

void Player::down() {
	this->_gMap->moveActor(this, _x, _y + 1);
}
