#pragma once

#include "Ship.h"
#include "ShipPosition.h"

#define BOARD_SIZE 10

class Board
{
	int** _board;
	Ship* _ships;
	int _size;

	void initBoard();
	void deleteBoard();
public:
	Board(Ship* ships);
	Board();
	~Board();

	Ship* getShips() const;
	void setShips(Ship* ships);

	int** getBoard() const;
	void setBoard(int** board, int size);

	int getSize() const;

	int at(int row, int col) const;
};