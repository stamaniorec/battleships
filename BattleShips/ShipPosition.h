#pragma once

struct ShipPosition
{
	int startRow;
	int startCol;
	int endRow;
	int endCol;

	ShipPosition(int startRow, int startCol, int endRow, int endCol);
	ShipPosition();
};
