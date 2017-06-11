#include <stdexcept>
#include "ShipPosition.h"

ShipPosition::ShipPosition(int startRow, int startCol, int endRow, int endCol) :
	start(startRow, startCol), end(endRow, endCol) {};

ShipPosition::ShipPosition()
{
	start.row = start.col = end.row = end.col = -1;
}

int ShipPosition::getSize() const
{
	int dWidth = this->end.col - this->start.col;
	int dHeight = this->end.row - this->start.row;

	return dWidth > 0 ? dWidth + 1 : dHeight + 1;
}

bool ShipPosition::isHorizontal() const
{
	return this->start.row == this->end.row;
}

bool ShipPosition::isVertical() const
{
	return this->start.col == this->end.col;
}