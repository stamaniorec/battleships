#pragma once

#include "ShipPosition.h"
#include "Ship.h"

class CarrierShip : public Ship
{
public:
	CarrierShip();
	CarrierShip(ShipPosition position);

	char getLetter() const override;
};