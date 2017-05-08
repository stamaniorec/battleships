#pragma once

#include "ShipPosition.h"
#include "Ship.h"

class BattleShip : public Ship
{
public:
	BattleShip();
	BattleShip(ShipPosition position);

	char getLetter() const override;
	const char* getName() const override;
};