#include "ShipPosition.h"

ShipPosition::ShipPosition(int startX, int startY, int endX, int endY) :
	startX(startX), startY(startY), endX(endX), endY(endY) {}

ShipPosition::ShipPosition()
{
	startX = startY = endX = endY = 0;
}