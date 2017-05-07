#pragma once

#include "Ship.h"
#include "ShipPosition.h"

#define BOARD_SIZE 10

enum BoardCellState
{
	FREE,
	OCCUPIED,
	MISSED,
	HIT
};

class Board
{
	int** _board;
	int _size;
	Ship** _ships;
	
	void initBoard();
	void deleteBoard();
public:
	Board(Ship** ships);
	Board();
	~Board();

	Ship** getShips() const;
	void setShips(Ship** ships);

	int** getBoard() const;
	void setBoard(int** board, int size);

	int getSize() const;

	int at(int row, int col) const;
	bool hasShipAt(int row, int col) const;
	Ship* getShipAt(int row, int col) const;
};