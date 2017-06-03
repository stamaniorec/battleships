#pragma once

#include "ShipPosition.h"
#include "Ship.h"
#include "Game.h"

class Game;

class DestroyerShip : public Ship
{
public:
	DestroyerShip();
	DestroyerShip(ShipPosition position);

	char getLetter() const override;
	const char* getName() const override;
	void executeSpecialMove(Game& game) override;
};