#include "SubmarineShip.h"

SubmarineShip::SubmarineShip(ShipPosition position) : position(position) {}

SubmarineShip::SubmarineShip() : position(6, 3, 6, 5), hp(3), size(3)
{
}

const ShipPosition& SubmarineShip::getPosition() const { return position; }
void SubmarineShip::setPosition(const ShipPosition& position) { this->position = position; }

int SubmarineShip::getHp() const { return hp; }
void SubmarineShip::setHp(int hp) { this->hp = hp; }

int SubmarineShip::getSize() const { return size; }
void SubmarineShip::setSize(int size) { this->size = size; }