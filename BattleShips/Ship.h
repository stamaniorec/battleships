#pragma once

#include "ShipPosition.h"

class Ship
{
	ShipPosition _position;
	int _hp;
	int _size;
public:
	Ship();
	Ship(ShipPosition position);
	Ship(ShipPosition position, int hp, int size);

	const ShipPosition& getPosition() const;
	void setPosition(const ShipPosition& position);

	int getHp() const;
	void setHp(int hp);

	int getSize() const;
	void setSize(int size);

	void hit(int damage);
	bool isAlive() const;

	virtual char getLetter() const = 0;
	virtual const char* getName() const = 0;
};