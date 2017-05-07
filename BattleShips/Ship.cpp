#include "Ship.h"

Ship::Ship() : _size(0), _hp(0) {}
Ship::Ship(ShipPosition position) : _position(position) {}

const ShipPosition& Ship::getPosition() const { return _position; }
void Ship::setPosition(const ShipPosition& position) { this->_position = position; }

int Ship::getHp() const { return _hp; }
void Ship::setHp(int hp) { this->_hp = hp; }

int Ship::getSize() const { return _size; }
void Ship::setSize(int size) { this->_size = size; }