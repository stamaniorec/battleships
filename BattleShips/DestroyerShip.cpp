#include "DestroyerShip.h"
#include "GameConfig.h"

DestroyerShip::DestroyerShip() :
	Ship({}, DESTROYER_SHIP_HP, DESTROYER_SHIP_SIZE) {}

DestroyerShip::DestroyerShip(ShipPosition position)
	: Ship(position, DESTROYER_SHIP_HP, DESTROYER_SHIP_SIZE) {}

char DestroyerShip::getLetter() const { return DESTROYER_SHIP_RENDER_LETTER; }