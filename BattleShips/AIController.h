#pragma once

#include "Game.h"

class AIController
{
	Game& _game;
	Player* _actualPlayer;
	Player* _ai;

	Ship* chooseShip() const;
	BoardPosition shoot();
public:
	AIController(Game& game);

	void playTurn();
};