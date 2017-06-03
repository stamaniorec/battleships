#pragma once

#include "ShipPosition.h"
#include "Ship.h"
#include "Game.h"

class CarrierShip : public Ship
{
public:
	CarrierShip();
	CarrierShip(ShipPosition position);

	char getLetter() const override;
	const char* getName() const override;
	void executeSpecialMove(Game& game) override;
};