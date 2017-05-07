#include "Board.h"
#include "CommonUtilities.h"
#include "CarrierShip.h"

void Board::initBoard()
{
	_board = new int*[BOARD_SIZE];

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		_board[i] = new int[BOARD_SIZE];
		
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_board[i][j] = 0;
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

Board::Board(Ship* ships) : _ships(ships), _size(BOARD_SIZE)
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

Ship* Board::getShips() const { return _ships; }
void Board::setShips(Ship* ships) { this->_ships = ships; }

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
