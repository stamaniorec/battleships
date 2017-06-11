#pragma once

#include <queue>
#include "Ship.h"
#include "GameConfig.h"

class ShipTurnVerifier
{
	bool _hasPlayedWith[NUM_SHIPS];
	std::queue<int> _queue;

	int mapLetterToIndex(char letter) const;
public:
	ShipTurnVerifier();

	void playWith(Ship* ship);
	bool canPlayWith(Ship* ship) const;
};
