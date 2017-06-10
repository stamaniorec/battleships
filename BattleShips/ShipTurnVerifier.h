#pragma once

#include <queue>
#include "Ship.h"

class ShipTurnVerifier
{
	bool _hasPlayedWith[Game::NUM_SHIPS];
	std::queue<int> _queue;

	int mapLetterToIndex(char letter) const;
public:
	ShipTurnVerifier();

	void playWith(Ship* ship);
	bool canPlayWith(Ship* ship) const;
};
