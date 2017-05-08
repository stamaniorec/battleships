#pragma once

#include "ShipPosition.h"
#include "Ship.h"

class CruiserShip : public Ship
{
public:
	CruiserShip();
	CruiserShip(ShipPosition position);

	char getLetter() const override;
	const char* getName() const override;
};
