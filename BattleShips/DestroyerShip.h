#pragma once

#include "ShipPosition.h"

class DestroyerShip
{
	ShipPosition position;
	int hp;
	int size;
public:
	DestroyerShip(ShipPosition position);
	DestroyerShip();

	const ShipPosition& getPosition() const;
	void setPosition(const ShipPosition& position);

	int getHp() const;
	void setHp(int hp);

	int getSize() const;
	void setSize(int size);
};