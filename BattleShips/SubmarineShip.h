#pragma once

#include "ShipPosition.h"
#include "Ship.h"
#include "Game.h"

class Game;

class SubmarineShip : public Ship
{
public:
	SubmarineShip();
	SubmarineShip(ShipPosition position);

	char getLetter() const override;
	const char* getName() const override;
	void play(Game& game) override;
};