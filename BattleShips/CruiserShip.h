#pragma once

#include "ShipPosition.h"

class CruiserShip
{
	ShipPosition position;
	int hp;
	int size;
public:
	CruiserShip(ShipPosition position);
	CruiserShip();

	const ShipPosition& getPosition() const;
	void setPosition(const ShipPosition& position);

	int getHp() const;
	void setHp(int hp);

	int getSize() const;
	void setSize(int size);
};
