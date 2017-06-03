#include "SubmarineShip.h"
#include "GameConfig.h"

SubmarineShip::SubmarineShip() :
	Ship({}, SUBMARINE_SHIP_HP, SUBMARINE_SHIP_SIZE) {}

SubmarineShip::SubmarineShip(ShipPosition position) :
	Ship(position, SUBMARINE_SHIP_HP, SUBMARINE_SHIP_SIZE) {}

char SubmarineShip::getLetter() const { return SUBMARINE_SHIP_RENDER_LETTER; }
const char* SubmarineShip::getName() const { return SUBMARINE_SHIP_DISPLAY_NAME; }

void SubmarineShip::executeSpecialMove(Game& game)
{
	game.playWithSubmarineShip();
}