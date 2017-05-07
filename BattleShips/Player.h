#pragma once

#include "Board.h"

class Player
{
	Board _board;
	char* _name;
	int _score;

	Ship** _ships;
public:
	Player();
	Player(char* name);

	~Player();

	const Board& getBoard() const;
	char* getName() const;
	int getScore() const;

	void generateShips();
};