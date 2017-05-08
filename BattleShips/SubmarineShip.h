#pragma once

#include "ShipPosition.h"
#include "Ship.h"

class SubmarineShip : public Ship
{
public:
	SubmarineShip();
	SubmarineShip(ShipPosition position);

	char getLetter() const override;
	const char* getName() const override;
};