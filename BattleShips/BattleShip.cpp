#include "BattleShip.h"
#include "GameConfig.h"

BattleShip::BattleShip() :
	Ship({}, BATTLE_SHIP_HP, BATTLE_SHIP_SIZE) {}

BattleShip::BattleShip(ShipPosition position)
	: Ship(position, BATTLE_SHIP_HP, BATTLE_SHIP_SIZE) {}

char BattleShip::getLetter() const { return BATTLE_SHIP_RENDER_LETTER; }
const char* BattleShip::getName() const { return BATTLE_SHIP_DISPLAY_NAME; }