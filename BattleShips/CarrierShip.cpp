#include "CarrierShip.h"

CarrierShip::CarrierShip(ShipPosition position) : position(position) {}

CarrierShip::CarrierShip() : position(2, 2, 2, 6), hp(5), size(5)
{
}

const ShipPosition& CarrierShip::getPosition() const { return position; }
void CarrierShip::setPosition(const ShipPosition& position) { this->position = position; }

int CarrierShip::getHp() const { return hp; }
void CarrierShip::setHp(int hp) { this->hp = hp; }

int CarrierShip::getSize() const { return size; }
void CarrierShip::setSize(int size) { this->size = size; }