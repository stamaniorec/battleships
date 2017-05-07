#include "CruiserShip.h"

CruiserShip::CruiserShip(ShipPosition position) : position(position) {}

CruiserShip::CruiserShip() : position(7, 4, 7, 6), hp(3), size(3)
{
}

const ShipPosition& CruiserShip::getPosition() const { return position; }
void CruiserShip::setPosition(const ShipPosition& position) { this->position = position; }

int CruiserShip::getHp() const { return hp; }
void CruiserShip::setHp(int hp) { this->hp = hp; }

int CruiserShip::getSize() const { return size; }
void CruiserShip::setSize(int size) { this->size = size; }