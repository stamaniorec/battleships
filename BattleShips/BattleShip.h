#pragma once

#include "ShipPosition.h"
#include "Ship.h"
#include "Game.h"

class BattleShip : public Ship
{
public:
	BattleShip();
	BattleShip(ShipPosition position);

	char getLetter() const override;
	const char* getName() const override;
	void executeSpecialMove(Game& game) override;
};