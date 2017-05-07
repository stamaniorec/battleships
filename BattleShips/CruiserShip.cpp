#include "CruiserShip.h"

CruiserShip::CruiserShip()
{
	// TODO: add check for matching size and position coordinates
	ShipPosition position(7, 4, 7, 6);
	setPosition(position);
	setHp(3);
	setSize(3);
}

CruiserShip::CruiserShip(ShipPosition position) : Ship(position)
{
	setHp(3);
	setSize(3);
}

char CruiserShip::getLetter() const { return 'R'; }