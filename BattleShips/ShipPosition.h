#pragma once

#include "BoardPosition.h"

struct ShipPosition
{
	BoardPosition start;
	BoardPosition end;

	ShipPosition(int startRow, int startCol, int endRow, int endCol);
	ShipPosition();

	int getSize() const;
	bool isHorizontal() const;
	bool isVertical() const;
};
