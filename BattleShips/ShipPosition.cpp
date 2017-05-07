#include "ShipPosition.h"

ShipPosition::ShipPosition(int startRow, int startCol, int endRow, int endCol) :
	startRow(startRow), startCol(startCol), endRow(endRow), endCol(endCol) {}

ShipPosition::ShipPosition()
{
	startRow = startCol = endRow = endCol = 0;
}