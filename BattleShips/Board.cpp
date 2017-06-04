#include "Board.h"
#include "CommonUtilities.h"
#include "CarrierShip.h"
#include "GameConfig.h"
#include "BoardCellState.h"

void Board::initBoard()
{
	_board = new int*[BOARD_SIZE];

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		_board[i] = new int[BOARD_SIZE];
		
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_board[i][j] = FREE;
		}
	}

	_board[8][8] = MISSED;
	_board[7][7] = MISSED;
	_board[9][9] = HIT;
}

void Board::deleteBoard()
{
	if (_board != nullptr)
	{
		for (int i = 0; i < _size; i++)
		{
			if (_board[i] != nullptr)
			{
				delete[] _board[i];
			}
		}

	}

	_board = nullptr;
}

Board::Board(Ship** ships) : _ships(ships), _size(BOARD_SIZE)
{
	initBoard();
}

Board::Board() : _ships(nullptr), _size(BOARD_SIZE)
{
	initBoard();
}

Board::~Board()
{
	deleteBoard();
}

Ship** Board::getShips() const { return _ships; }

void Board::setShips(Ship** ships)
{
	this->_ships = ships;

	for (int i = 0; i < 5; i++)
	{
		markOnBoard(ships[i]->getPosition());
	}
}

void Board::markOnBoard(const ShipPosition& position)
{
	for (int j = position.startRow; j <= position.endRow; j++)
	{
		this->_board[j][position.startCol] = OCCUPIED;
	}

	for (int j = position.startCol; j <= position.endCol; j++)
	{
		this->_board[position.startRow][j] = OCCUPIED;
	}
}

int** Board::getBoard() const { return _board; }

void Board::setBoard(int** board, int size)
{
	deleteBoard();
	this->_board = board;
	this->_size = size;
}

int Board::getSize() const
{
	return _size;
}

int Board::at(int row, int col) const
{
	return _board[row][col];
}

bool Board::hasShipAt(int row, int col) const
{
	return _board[row][col] == OCCUPIED;
}

bool Board::shipOccupies(Ship* ship, int row, int col) const
{
	ShipPosition position = ship->getPosition();

	return position.startRow <= row && position.endRow >= row &&
		position.startCol <= col && position.endCol >= col;
}

Ship* Board::getShipAt(int row, int col) const
{
	for (int i = 0; i < 5; i++)
	{
		Ship* ship = _ships[i];

		if (shipOccupies(ship, row, col) && ship->isAlive())
		{
			return ship;
		}
	}

	return nullptr;
}

void Board::strike(const ShipPosition& targetCell)
{
	Ship* shipHit = getShipAt(targetCell.startRow, targetCell.startCol);
	
	if (shipHit != nullptr)
	{
		shipHit->hit(1);
		_board[targetCell.startRow][targetCell.startCol] = HIT;
	}
	else
	{
		_board[targetCell.startRow][targetCell.startCol] = MISSED;
	}
}