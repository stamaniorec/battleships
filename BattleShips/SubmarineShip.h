#pragma once

#include "ShipPosition.h"

class SubmarineShip
{
	ShipPosition position;
	int hp;
	int size;
public:
	SubmarineShip(ShipPosition position);
	SubmarineShip();

	const ShipPosition& getPosition() const;
	void setPosition(const ShipPosition& position);

	int getHp() const;
	void setHp(int hp);

	int getSize() const;
	void setSize(int size);
};