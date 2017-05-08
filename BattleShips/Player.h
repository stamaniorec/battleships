#pragma once

#include "Board.h"
#include "ShipTurnVerifier.h"

class Player
{
	Board _board;
	char* _name;
	int _score;

	Ship** _ships;
	ShipTurnVerifier _shipTurnVerifier;
public:
	Player();
	Player(char* name);

	~Player();

	Board& getBoard();
	char* getName() const;
	int getScore() const;

	void generateShips();
	bool hasShipWithLetter(char letter) const;
	Ship* getShipWithLetter(char letter) const;

	bool canPlayWith(Ship* ship) const;
	Ship* playWith(Ship* ship);
};