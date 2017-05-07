#include "SubmarineShip.h"

SubmarineShip::SubmarineShip()
{
	// TODO: add check for matching size and position coordinates
	ShipPosition position(6, 3, 6, 5);
	setPosition(position);
	setHp(3);
	setSize(3);
}

SubmarineShip::SubmarineShip(ShipPosition position) : Ship(position)
{
	setHp(3);
	setSize(3);
}

char SubmarineShip::getLetter() const { return 'S'; }