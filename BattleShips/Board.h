#pragma once

#include "Ship.h"
#include "ShipPosition.h"

class Board
{
	int** _board;
	int _size;
	Ship** _ships;
	
	void initBoard();
	void deleteBoard();
	void markOnBoard(const ShipPosition& position);
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
	bool shipOccupies(Ship* ship, int row, int col) const;
};