#include <stdexcept>
#include "ShipPosition.h"

ShipPosition::ShipPosition(int startRow, int startCol, int endRow, int endCol) :
	startRow(startRow), startCol(startCol), endRow(endRow), endCol(endCol)
{
	if (startRow != endRow && startCol != endCol)
	{
		throw std::invalid_argument("Position is neither vertical nor horizontal");
	}
}

ShipPosition::ShipPosition()
{
	startRow = startCol = endRow = endCol = 0;
}

int ShipPosition::getSize() const
{
	int dWidth = this->endCol - this->startCol;
	int dHeight = this->endRow - this->startRow;

	return dWidth > 0 ? dWidth + 1 : dHeight + 1;
}

bool ShipPosition::isHorizontal() const
{
	return this->startRow == this->endRow;
}

bool ShipPosition::isVertical() const
{
	return !isHorizontal();
}