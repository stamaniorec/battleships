#include "BattleShip.h"

BattleShip::BattleShip()
{
	ShipPosition position(4, 5, 4, 8);
	setPosition(position);
	setHp(4);
	setSize(4);
}
