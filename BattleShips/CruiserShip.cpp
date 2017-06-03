#include "CruiserShip.h"
#include "GameConfig.h"

CruiserShip::CruiserShip() :
	Ship({}, CRUISER_SHIP_HP, CRUISER_SHIP_SIZE) {}

CruiserShip::CruiserShip(ShipPosition position) :
	Ship(position, CRUISER_SHIP_HP, CRUISER_SHIP_SIZE) {}

char CruiserShip::getLetter() const { return CRUISER_SHIP_RENDER_LETTER; }
const char* CruiserShip::getName() const { return CRUISER_SHIP_DISPLAY_NAME; }

void CruiserShip::executeSpecialMove(Game& game)
{
	game.playWithCruiserShip();
}