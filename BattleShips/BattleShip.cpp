#include "BattleShip.h"

BattleShip::BattleShip()
{
	// TODO: add check for matching size and position coordinates
	ShipPosition position(4, 5, 4, 8);
	setPosition(position);
	setHp(4);
	setSize(4);
}

BattleShip::BattleShip(ShipPosition position) : Ship(position)
{
	setHp(4);
	setSize(4);
}

char BattleShip::getLetter() const { return 'B'; }