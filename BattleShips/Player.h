#pragma once

#include "Board.h"

class Player
{
	Board _board;
	char* _name;
	int _score;
public:
	Player();
	Player(char* name);

	const Board& getBoard() const;
	char* getName() const;
	int getScore() const;

	void generateShips();
};