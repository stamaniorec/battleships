#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <ctype.h>
#include "Game.h"
#include "BoardCellState.h"
#include "GameConfig.h"
#include "CruiserShip.h"

#include <chrono>
#include <thread>

using namespace std;

Game::Game() {}

const int Game::NUM_SHIPS = 5;

const char* Game::SHIP_LETTERS[] = {
	BATTLE_SHIP_RENDER_LETTER,
	CARRIER_SHIP_RENDER_LETTER,
	CRUISER_SHIP_RENDER_LETTER,
	DESTROYER_SHIP_RENDER_LETTER,
	SUBMARINE_SHIP_RENDER_LETTER
};

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

	_isGameOver = false;
	_lastPlayedWith = nullptr;

	_player->generateShips(); // TODO: get it from UI
	_enemy->generateShips();

	srand(time(NULL));
}



char Game::enterLetter() const
{
	char letter = 0;

	while (!isalpha(letter))
	{
		cout << PROMPT;

		cin.get(letter);

		if (letter == '\n')
		{
			continue;
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return letter;
}

Ship* Game::chooseShipToPlayWith()
{
	renderShipChoicePrompt();

	Ship* selectedShip = nullptr;

	while (!_player->canPlayWith(selectedShip))
	{
		if (selectedShip)
		{
			cout << "You are not yet allowed to play with " << selectedShip->getName() << endl;
		}

		char letter = enterLetter();

		if (!_player->hasShipWithLetter(letter))
		{
			cout << "Invalid letter \"" << letter << "\". Try again!" << endl;
			selectedShip = nullptr;
			continue;
		}

		selectedShip = _player->getShipWithLetter(letter);
	}

	_lastPlayedWith = selectedShip;
	
	cout << endl;
	return _player->playWith(selectedShip);
}

const BoardPosition& Game::chooseTarget()
{
	cout << "Enter row and column number to shoot at..." << endl;
	cout << PROMPT;

	BoardPosition position;
	cin >> position;

	while (!Board::isValidPosition(position))
	{
		cout << "Please enter valid row and column numbers in the format <row> <col>!" << endl;
		cout << PROMPT;

		cin >> position;
	}

	return position;
}

void Game::playerTurn()
{
	render();

	cout << endl;

	Ship* ship = chooseShipToPlayWith();
	cout << "You're playing with " << ship->getName() << endl;
	
	ship->play(*this);
}

BoardPosition Game::shoot()
{
	BoardPosition target = chooseTarget();

	cout << endl;
	cout << "You're shooting at " << target.row << " " << target.col << endl;

	_enemy->getBoard().strike(target);

	Ship* shipHit = _enemy->getBoard().getShipAt(target.row, target.col);
	if (shipHit != nullptr)
	{
		if (!shipHit->isAlive())
		{
			cout << "You sunk " << shipHit->getName() << endl;
		}
		else
		{
			cout << "You hit " << shipHit->getName() << " but it ain't sunk yet!" << endl;
		}
	}
	else
	{
		cout << "Well... You missed." << endl;
	}

	cout << endl;
	waitToContinue();

	return target;
}

void Game::playWithCarrierShip()
{
	shoot();

	cout << endl;
	cout << "Special move for Carrier ship - perform a second shooting!" << endl;
	
	shoot();
}

void Game::playWithBattleShip()
{
	BoardPosition target = shoot();

	cout << endl;
	cout << "Special move for Battle ship - adjacent fields will be revealed!" << endl;
	this->renderEnemyBoardWithRevealedAdjacent(_enemy->getBoard(), target);
	
	cout << endl;
	waitToContinue();
}

void Game::playWithCruiserShip()
{
}

void Game::playWithDestroyerShip()
{
	shoot();

	cout << endl;
	cout << "Special ability of Destroyer ship - a protection shield for your ships for one turn." << endl;
}

void Game::playWithSubmarineShip()
{
	shoot();
	
	cout << endl;
	cout << "Special move for Submarine ship - 70% chance of the enemy missing your ship!" << endl;
}

void Game::recoverCruiserHealth()
{
	Ship* cruiser = _player->getShipWithLetter('R');
	int newHp = (cruiser->getHp() + 1) % 5;
	cruiser->setHp(newHp);
}

bool Game::hasSeventyPercentChanceOfMissing() const
{
	return this->_lastPlayedWith->getName() == SUBMARINE_SHIP_DISPLAY_NAME;
}

bool Game::hasDestroyerShield() const
{
	return this->_lastPlayedWith->getName() == DESTROYER_SHIP_DISPLAY_NAME;
}

bool Game::hasCruiserRecoveryEnabled() const
{
	return this->_lastPlayedWith->getName() == CRUISER_SHIP_DISPLAY_NAME;
}

void Game::enemyTurn()
{
	clearScreen();
	render();

	Ship* ship = nullptr;
	while (!ship)
	{
		int shipLetterIndex = rand() % 5;
		ship = _enemy->getShipWithLetter(Game::SHIP_LETTERS[shipLetterIndex]);
	}

	int randRow = rand() % BOARD_SIZE;
	int randCol = rand() % BOARD_SIZE;

	BoardPosition target(randRow, randCol);

	cout << "Enemy is shooting at " << randRow << "," << randCol << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	_player->getBoard().strike(target);

	Ship* shipHit = _player->getBoard().getShipAt(target.row, target.col);
	if (shipHit != nullptr)
	{
		if (hasSeventyPercentChanceOfMissing())
		{
			int randNum = rand() % 10;
			if (randNum < 7)
			{
				cout << "Enemy was going to hit you, but your 70% chance of the AI missing saved your ass!" << endl;
			}
		}

		if (hasDestroyerShield())
		{
			cout << "Enemy hit " << shipHit->getName() << " but you have a shield from the destroyer so you're all good!" << endl;
		}
		else
		{
			if (shipHit->getName() != CRUISER_SHIP_DISPLAY_NAME && hasCruiserRecoveryEnabled())
			{
				cout << "Special power for cruiser! Recovering 1 health!" << endl;

				this->recoverCruiserHealth();
			}
			else if (shipHit->isAlive())
			{
				cout << "Enemy hit " << shipHit->getName() << endl;
			}
			else
			{
				cout << "The ship " << shipHit->getName() << " was sunk... :(" << endl;
			}
		}
	}
	else
	{
		if (this->hasCruiserRecoveryEnabled())
		{
			cout << "Special power for cruiser! Recovering 1 health!" << endl;

			this->recoverCruiserHealth();
		}

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

void Game::renderEnemyBoardWithRevealedAdjacent(const Board& board, const BoardPosition& position) const
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
				if (Board::areAdjacent(position, BoardPosition(i, j)))
				{
					cout << "O";
				}
				else
				{
					cout << FREE_CELL_CHAR;
				}
			}

			cout << CELL_SEPARATOR_CHAR;
		}

		cout << endl;
	}
}

void Game::clearScreen() const
{
	system("cls");
}

void Game::waitToContinue() const
{
	cout << "Press a key to continue..." << endl;
	cout << PROMPT;

	cin.get();
	cin.clear();
}

void Game::renderShipChoicePrompt() const
{
	cout << "Available ships: " << endl;
	cout << endl;

	Ship** allPlayerShips = _player->getBoard().getShips();

	for (int i = 0; i < NUM_SHIPS; i++)
	{
		Ship* ship = allPlayerShips[i];

		if (ship->isAlive() && _player->canPlayWith(ship))
		{
			cout << ship->getName() << "(" << ship->getLetter() << "), " << endl;
		}
	}

	cout << endl;
	cout << "Enter letter for ship to play with..." << endl;
}