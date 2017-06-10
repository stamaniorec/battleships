#pragma once

#include <iostream>

using namespace std;

struct BoardPosition
{
	int row;
	int col;

	BoardPosition();
	BoardPosition(int row, int col);

	friend istream& operator >> (istream& in, BoardPosition& position);
};
