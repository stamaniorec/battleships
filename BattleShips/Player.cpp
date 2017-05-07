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
		for (int i = 0; i < 5; i++)
		{
			if (_ships[i] != nullptr)
			{
				delete _ships[i];
			}
		}

		delete[] _ships;
	}
}

const Board& Player::getBoard() const
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
	Ship** ships = new Ship*[5];
	
	ships[0] = new BattleShip({ 0, 0, 0, 4 });
	ships[1] = new CarrierShip({ 1, 0, 1, 4 });
	ships[2] = new CruiserShip({ 2, 0, 2, 4 });
	ships[3] = new DestroyerShip({ 3, 0, 3, 4 });
	ships[4] = new SubmarineShip({ 4, 0, 4, 4 });

	this->_ships = ships;
	_board.setShips(ships);
}