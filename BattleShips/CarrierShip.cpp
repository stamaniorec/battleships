#include "CarrierShip.h"

CarrierShip::CarrierShip()
{
	// TODO: add check for matching size and position coordinates
	ShipPosition position(2, 2, 2, 6);
	setPosition(position);
	setHp(5);
	setSize(5);
}

CarrierShip::CarrierShip(ShipPosition position) : Ship(position)
{
	setHp(5);
	setSize(5);
}

char CarrierShip::getLetter() const { return 'C'; }