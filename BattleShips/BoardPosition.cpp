#include <string>
#include <sstream>
#include "BoardPosition.h"

BoardPosition::BoardPosition(int row, int col) : row(row), col(col) {};
BoardPosition::BoardPosition() {};

istream& operator >> (istream& in, BoardPosition& position)
{
	string input;
	getline(cin, input);

	int row, col;

	stringstream ss(input);
	ss >> row >> col;
	
	if (ss.fail())
	{
		position.row = position.col = -1;
	}
	else
	{
		position.row = row;
		position.col = col;
	}

	return in;
}