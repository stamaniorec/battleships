#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "BoardCellState.h"
#include "GameConfig.h"

#include <chrono>
#include <thread>

using namespace std;

Game::Game() : _isGameOver(false)
{
}

Game::~Game()
{
	if (_player != nullptr)
	{
		delete _player;
	}

	if (_enemy != nullptr)
	{
		delete _enemy;
	}
}

void Game::run()
{
	init();

	while (!_isGameOver)
	{
		playerTurn();
		enemyTurn();
	}
}

void Game::init()
{
	_player = new Player("Player");
	_enemy = new Player("Enemy");

	_player->generateShips(); // TODO: get it from UI
	_enemy->generateShips();

	srand(time(NULL));
}

void Game::renderShipChoicePrompt() const
{
	cout << "Available ships: ";

	Ship** allPlayerShips = _player->getBoard().getShips();

	for (int i = 0; i < 5; i++)
	{
		Ship* ship = allPlayerShips[i];

		if (ship->isAlive() && _player->canPlayWith(ship))
		{
			cout << ship->getName() << "(" << ship->getLetter() << "), " << endl;
		}
	}
}

Ship* Game::chooseShipToPlayWith() const
{
	renderShipChoicePrompt();

	char letter;
	while (true)
	{
		cin.get(letter);

		if (letter == '\n')
		{
			continue;
		}

		if (!_player->hasShipWithLetter(letter))
		{
			cout << "Ship with letter " << letter << " isn't available, try again." << endl;
			continue;
		}

		Ship* selectedShip = _player->getShipWithLetter(letter);

		if (_player->canPlayWith(selectedShip))
		{
			break;
		}
		else
		{
			cout << "You are not yet allowed to play with " << selectedShip->getName() << endl;
		}
	}

	Ship* selectedShip = _player->getShipWithLetter(letter);
	return _player->playWith(selectedShip);
}

const ShipPosition& Game::chooseTarget() const
{
	int row, col;
	cin >> row >> col;

	while (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
	{
		cout << "Please select a position on the board!" << endl;
		cin >> row >> col;
	}

	return ShipPosition(row, col, row, col);
}

void Game::playerTurn()
{
	render();

	Ship* ship = chooseShipToPlayWith();
	cout << "You're playing with " << ship->getName() << endl;
	
	ship->executeSpecialMove(*this);
}

void Game::playWithCarrierShip()
{
	ShipPosition target = chooseTarget();
	cout << "You're shooting at " << target.startRow << " " << target.startCol << endl;

	_enemy->getBoard().strike(target);

	Ship* shipHit = _enemy->getBoard().getShipAt(target.startRow, target.startCol);
	if (shipHit != nullptr)
	{
		if (!shipHit->isAlive())
		{
			cout << "You sunk " << shipHit->getName() << endl;
		}
	}

	cout << "Special move for carrier - choose a second target!" << endl;
	target = chooseTarget();
	cout << "You're again shooting at " << target.startRow << " " << target.startCol << endl;

	_enemy->getBoard().strike(target);

	shipHit = _enemy->getBoard().getShipAt(target.startRow, target.startCol);
	if (shipHit != nullptr)
	{
		if (!shipHit->isAlive())
		{
			cout << "You sunk " << shipHit->getName() << endl;
		}
	}
}

void Game::playWithBattleShip()
{
	ShipPosition target = chooseTarget();
	cout << "You're shooting at " << target.startRow << " " << target.startCol << endl;

	cout << "Special move for carrier - choose a second target!" << endl;
	target = chooseTarget();
	cout << "You're again shooting at " << target.startRow << " " << target.startCol << endl;

	_enemy->getBoard().strike(target);

	Ship* shipHit = _enemy->getBoard().getShipAt(target.startRow, target.startCol);
	if (shipHit != nullptr)
	{
		if (!shipHit->isAlive())
		{
			cout << "You sunk " << shipHit->getName() << endl;
		}
	}
}

void Game::playWithCruiserShip()
{

}

void Game::playWithDestroyerShip()
{

}

void Game::playWithSubmarineShip()
{

}

void Game::enemyTurn()
{
	system("cls"); // clear screen in Windows
	render();

	char letters[] = { 'B', 'C', 'R', 'D', 'S' };

	Ship* ship = nullptr;
	while (ship == nullptr)
	{
		int shipLetterIndex = rand() % 5;
		ship = _enemy->getShipWithLetter(letters[shipLetterIndex]);
	}

	int randRow = rand() % BOARD_SIZE;
	int randCol = rand() % BOARD_SIZE;

	ShipPosition target(randRow, randCol, randRow, randCol);

	cout << "Enemy is shooting at " << randRow << "," << randCol << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	_player->getBoard().strike(target);

	Ship* shipHit = _player->getBoard().getShipAt(target.startRow, target.startCol);
	if (shipHit != nullptr)
	{
		if (!shipHit->isAlive())
		{
			cout << "The ship " << shipHit->getName() << " was sunk... :(" << endl;
		}
		else
		{
			cout << "Enemy hit " << shipHit->getName() << endl;
		}
	}
	else
	{
		cout << "Enemy missed! Pheeeew!" << endl;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Game::render() const
{
	renderPlayerStats(*_enemy);
	renderEnemyBoard(_enemy->getBoard());
	renderSeparator();
	renderPlayerBoard(_player->getBoard());
	renderPlayerStats(*_player);
}

void Game::renderPlayerStats(const Player& player) const
{
	cout << "Player: " << player.getName() << "; Score: " << player.getScore() << endl;
}

void Game::renderPlayerBoard(const Board& board) const
{
	for (int i = 0; i < board.getSize(); i++)
	{
		for (int j = 0; j < board.getSize(); j++)
		{
			if (board.at(i, j) == FREE)
			{
				cout << FREE_CELL_CHAR;
			}
			else if (board.at(i, j) == MISSED)
			{
				cout << MISSED_CELL_CHAR;
			}
			else if (board.at(i, j) == HIT)
			{
				cout << HIT_CELL_CHAR;
			}
			else if (board.at(i, j) == OCCUPIED)
			{
				Ship* ship = board.getShipAt(i, j);

				if (!ship)
				{
					throw std::runtime_error("No ship at given position.");
				}

				cout << ship->getLetter();
			}

			cout << CELL_SEPARATOR_CHAR;
		}

		cout << endl;
	}
}

void Game::renderEnemyBoard(const Board& board) const
{
	for (int i = 0; i < board.getSize(); i++)
	{
		for (int j = 0; j < board.getSize(); j++)
		{
			if (board.at(i, j) == FREE)
			{
				cout << FREE_CELL_CHAR;
			}
			else if (board.at(i, j) == MISSED)
			{
				cout << MISSED_CELL_CHAR;
			}
			else if (board.at(i, j) == HIT)
			{
				cout << HIT_CELL_CHAR;
			}
			else if (board.at(i, j) == OCCUPIED)
			{
				cout << FREE_CELL_CHAR;
			}

			cout << CELL_SEPARATOR_CHAR;
		}

		cout << endl;
	}
}

void Game::renderSeparator() const
{
	cout << FIELD_SEPARATOR_STRING << endl;
	cout << FIELD_SEPARATOR_STRING << endl;
}