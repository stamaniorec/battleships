#include <chrono>
#include <thread>
#include <ctime>

#include "AIController.h"
#include "GameConfig.h"
#include "BattleShip.h"
#include "CarrierShip.h"
#include "CruiserShip.h"
#include "DestroyerShip.h"
#include "SubmarineShip.h"

AIController::AIController(Game& game) :
	_game(game), _actualPlayer(game.getPlayer()), _ai(game.getEnemy())
{
	srand(time(NULL));
}

void AIController::playTurn()
{
	Ship* ship = chooseShip();

	cout << endl;

	BoardPosition target = shoot();
	Ship* shipHit = _game.getPlayer()->getBoard().getShipAt(target.row, target.col);
	
	cout << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	if (shipHit)
	{
		if (_game.hasSeventyPercentChanceOfMissing())
		{
			int randNum = rand() % 10;
			if (randNum < 7)
			{
				cout << "Enemy was going to hit you, but your 70% chance of the AI missing saved you!" << endl;
			}
		}

		if (_game.hasDestroyerShield())
		{
			cout << "Enemy hit " << shipHit->getName() << " but you have a shield from the destroyer so all is good!" << endl;
		}
		else
		{
			if (shipHit->getName() != CRUISER_SHIP_DISPLAY_NAME && _game.hasCruiserRecoveryEnabled())
			{
				cout << "Special power for cruiser! Recovering 1 health!" << endl;

				_game.recoverCruiserHealth();
			}
			else if (shipHit->isAlive())
			{
				cout << "Enemy hit " << shipHit->getName() << " but it's still staying strong!" << endl;
			}
			else
			{
				cout << "The ship " << shipHit->getName() << " was sunk... :(" << endl;
			}
		}
	}
	else
	{
		if (_game.hasCruiserRecoveryEnabled())
		{
			cout << "Special power for cruiser! Recovering 1 health!" << endl;

			_game.recoverCruiserHealth();
		}

		cout << "Enemy missed! Pheeeew!" << endl;
	}

	cout << endl;
	GameRenderer::waitToContinue();
}

Ship* AIController::chooseShip() const
{
	Ship* ship = nullptr;

	while (!ship)
	{
		int shipLetterIndex = rand() % 5;
		ship = _ai->getShipWithLetter(Game::SHIP_LETTERS[shipLetterIndex]);
	}

	return ship;
}

BoardPosition AIController::shoot()
{
	int randRow = rand() % BOARD_SIZE;
	int randCol = rand() % BOARD_SIZE;

	BoardPosition target(randRow, randCol);

	cout << "Enemy is shooting at " << randRow << "," << randCol << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	_game.getPlayer()->getBoard().strike(target);

	return target;
}

ShipPosition AIController::generatePosition(const Ship& ship) const
{
	while (true)
	{
		bool horizontal = rand() % 2;
		bool vertical = !horizontal;

		int startRow = rand() % (BOARD_SIZE - ship.getSize());
		int startCol = rand() % (BOARD_SIZE - ship.getSize());
		int endRow;
		int endCol;

		if (horizontal)
		{
			endRow = startRow;
			endCol = startCol + ship.getSize() - 1;
		}
		else if (vertical)
		{
			endCol = startCol;
			endRow = startRow + ship.getSize() - 1;
		}

		ShipPosition position(startRow, startCol, endRow, endCol);

		if (_ai->getBoard().isShipPositionFree(position))
		{
			return position;
		}
	}
}

void AIController::generateShips()
{
	Ship** ships = new Ship*[NUM_SHIPS];

	ships[0] = new BattleShip();
	ships[1] = new CarrierShip();
	ships[2] = new CruiserShip();
	ships[3] = new DestroyerShip();
	ships[4] = new SubmarineShip();

	ships[0]->setPosition(generatePosition(*ships[0]));
	_ai->getBoard().setShip(ships[0], 0);

	ships[1]->setPosition(generatePosition(*ships[1]));
	_ai->getBoard().setShip(ships[1], 1);


	ships[2]->setPosition(generatePosition(*ships[2]));
	_ai->getBoard().setShip(ships[2], 2);

	ships[3]->setPosition(generatePosition(*ships[3]));
	_ai->getBoard().setShip(ships[3], 3);

	ships[4]->setPosition(generatePosition(*ships[4]));
	_ai->getBoard().setShip(ships[4], 4);

	_ai->getBoard().setShips(ships);
	_ai->setShips(ships);
	
}