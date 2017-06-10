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

	for (int i = 0; i < Game::NUM_SHIPS; i++)
	{
		markOnBoard(ships[i]->getPosition());
	}
}

void Board::markOnBoard(const ShipPosition& position)
{
	for (int j = position.start.row; j <= position.end.row; j++)
	{
		this->_board[j][position.start.col] = OCCUPIED;
	}

	for (int j = position.start.col; j <= position.end.col; j++)
	{
		this->_board[position.start.row][j] = OCCUPIED;
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

	return position.start.row <= row && position.end.row >= row &&
		position.start.col <= col && position.end.col >= col;
}

Ship* Board::getShipAt(int row, int col) const
{
	for (int i = 0; i < Game::NUM_SHIPS; i++)
	{
		Ship* ship = _ships[i];

		if (shipOccupies(ship, row, col) && ship->isAlive())
		{
			return ship;
		}
	}

	return nullptr;
}

void Board::strike(const BoardPosition& targetCell)
{
	Ship* shipHit = getShipAt(targetCell.row, targetCell.col);
	
	if (shipHit != nullptr)
	{
		shipHit->hit(1);
		_board[targetCell.row][targetCell.col] = HIT;
	}
	else
	{
		_board[targetCell.row][targetCell.col] = MISSED;
	}
}

bool Board::isValidPosition(const BoardPosition& position)
{
	return position.row >= 0 && position.row < BOARD_SIZE &&
		position.col >= 0 && position.col < BOARD_SIZE;
}

bool Board::areAdjacent(const BoardPosition& a, const BoardPosition& b)
{
	if (!Board::isValidPosition(a) || !Board::isValidPosition(b))
	{
		return false;
	}

	int deltaX = abs(a.col - b.col);
	int deltaY = abs(a.row - b.row);
	return deltaX <= 1 && deltaY <= 1;
}