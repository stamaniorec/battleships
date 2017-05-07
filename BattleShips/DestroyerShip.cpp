#include "DestroyerShip.h"

DestroyerShip::DestroyerShip()
{
	// TODO: add check for matching size and position coordinates
	ShipPosition position(9, 9, 8, 9);
	setPosition(position);
	setHp(2);
	setSize(2);
}

DestroyerShip::DestroyerShip(ShipPosition position) : Ship(position)
{
	setHp(2);
	setSize(2);
}

char DestroyerShip::getLetter() const { return 'D'; }