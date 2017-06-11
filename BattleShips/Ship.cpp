#include <stdexcept>
#include "Ship.h"

Ship::Ship() : _size(0), _hp(0) {}

Ship::Ship(ShipPosition position) : _position(position)
{
	this->_hp = this->_size = position.getSize();
}

Ship::Ship(ShipPosition position, int hp, int size) :
	_position(position), _hp(hp), _size(size) {};

const ShipPosition& Ship::getPosition() const { return _position; }

void Ship::setPosition(const ShipPosition& position)
{
	if (position.getSize() != _size)
	{
		throw std::invalid_argument("Given position doesn't match ship size.");
	}

	this->_position = position;
}

int Ship::getHp() const { return _hp; }
void Ship::setHp(int hp) { this->_hp = hp; }

int Ship::getSize() const { return _size; }
void Ship::setSize(int size) { this->_size = size; }

bool Ship::isAlive() const { return this->_hp > 0; }

void Ship::hit(int damage)
{
	_hp -= damage;
}