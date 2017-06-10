#include "Player.h"
#include "BattleShip.h"
#include "CarrierShip.h"
#include "CruiserShip.h"
#include "DestroyerShip.h"
#include "SubmarineShip.h"

Player::Player(char* name) : _name(name), _score(0), _ships(nullptr) {}

Player::Player() : _score(0), _name(nullptr), _ships(nullptr) {};

Player::~Player()
{
	if (_ships != nullptr)
	{
		for (int i = 0; i < Game::NUM_SHIPS; i++)
		{
			if (_ships[i] != nullptr)
			{
				delete _ships[i];
			}
		}

		delete[] _ships;
	}
}

Board& Player::getBoard()
{
	return _board;
}

char* Player::getName() const
{
	return _name;
}

int Player::getScore() const
{
	return _score;
}

void Player::generateShips()
{
	Ship** ships = new Ship*[Game::NUM_SHIPS];
	
	ships[0] = new BattleShip({ 0, 0, 0, 3 });
	ships[1] = new CarrierShip({ 1, 0, 1, 4 });
	ships[2] = new CruiserShip({ 2, 0, 2, 2 });
	ships[3] = new DestroyerShip({ 3, 0, 3, 1 });
	ships[4] = new SubmarineShip({ 4, 0, 4, 2 });

	this->_ships = ships;
	_board.setShips(ships);
}

bool Player::hasShipWithLetter(char letter) const
{
	return getShipWithLetter(letter) != nullptr;
}

Ship* Player::getShipWithLetter(char letter) const
{
	for (int i = 0; i < Game::NUM_SHIPS; i++)
	{
		Ship* ship = this->_ships[i];

		if (ship->isAlive() && ship->getLetter() == letter)
		{
			return ship;
		}
	}

	return nullptr;
}

bool Player::canPlayWith(Ship* ship) const
{
	return _shipTurnVerifier.canPlayWith(ship);
}

Ship* Player::playWith(Ship* ship)
{
	_shipTurnVerifier.playWith(ship);
	return ship;
}