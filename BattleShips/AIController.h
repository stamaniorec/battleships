#pragma once

#include "Game.h"

class AIController
{
	Game& _game;
	Player* _actualPlayer;
	Player* _ai;

	Ship* chooseShip() const;
	BoardPosition shoot();
	ShipPosition generatePosition(const Ship& ship) const;
public:
	AIController(Game& game);

	void generateShips();
	void playTurn();
};