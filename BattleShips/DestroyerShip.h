#pragma once

#include "ShipPosition.h"
#include "Ship.h"

class DestroyerShip : public Ship
{
public:
	DestroyerShip();
	DestroyerShip(ShipPosition position);

	char getLetter() const override;
};