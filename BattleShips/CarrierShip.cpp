#include "CarrierShip.h"
#include "GameConfig.h"

CarrierShip::CarrierShip() :
	Ship({}, CARRIER_SHIP_HP, CARRIER_SHIP_SIZE) {}

CarrierShip::CarrierShip(ShipPosition position) :
	Ship(position, CARRIER_SHIP_HP, CARRIER_SHIP_SIZE) {}

char CarrierShip::getLetter() const { return CARRIER_SHIP_RENDER_LETTER; }
const char* CarrierShip::getName() const { return CARRIER_SHIP_DISPLAY_NAME; }

void CarrierShip::executeSpecialMove(Game& game)
{
	game.playWithCarrierShip();
}