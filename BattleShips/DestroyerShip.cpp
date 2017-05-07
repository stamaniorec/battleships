#include "DestroyerShip.h"

DestroyerShip::DestroyerShip(ShipPosition position) : position(position) {}

DestroyerShip::DestroyerShip() : position(9, 9, 8, 9), hp(2), size(2)
{
}

const ShipPosition& DestroyerShip::getPosition() const { return position; }
void DestroyerShip::setPosition(const ShipPosition& position) { this->position = position; }

int DestroyerShip::getHp() const { return hp; }
void DestroyerShip::setHp(int hp) { this->hp = hp; }

int DestroyerShip::getSize() const { return size; }
void DestroyerShip::setSize(int size) { this->size = size; }