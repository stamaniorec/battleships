#include <iostream>

#include "Game.h"
#include "BoardCellState.h"
#include "GameConfig.h"
#include "CruiserShip.h"
#include "InputUtilities.h"

using namespace std;

Game::Game() {}

const int Game::NUM_SHIPS = 5;

const char Game::SHIP_LETTERS[] = {
	BATTLE_SHIP_RENDER_LETTER,
	CARRIER_SHIP_RENDER_LETTER,
	CRUISER_SHIP_RENDER_LETTER,
	DESTROYER_SHIP_RENDER_LETTER,
	SUBMARINE_SHIP_RENDER_LETTER
};

Game::~Game()
{
	if (_player)
	{
		delete _player;
	}

	if (_enemy)
	{
		delete _enemy;
	}

	if (_enemyController)
	{
		delete _enemyController;
	}

	if (_gameRenderer)
	{
		delete _gameRenderer;
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

	_enemyController = new AIController(*this);
	_gameRenderer = new GameRenderer(*this);
}

Ship* Game::chooseShipToPlayWith()
{
	_gameRenderer->renderShipChoicePrompt();

	Ship* selectedShip = nullptr;

	while (!_player->canPlayWith(selectedShip))
	{
		if (selectedShip)
		{
			cout << "You are not yet allowed to play with " << selectedShip->getName() << endl;
		}

		char letter = InputUtilities::enterLetter();

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
	_gameRenderer->render();

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
	GameRenderer::waitToContinue();

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
	_gameRenderer->renderEnemyBoardWithRevealedAdjacent(_enemy->getBoard(), target);
	
	cout << endl;
	GameRenderer::waitToContinue();
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
	GameRenderer::clearScreen();
	_gameRenderer->render();

	_enemyController->playTurn();
}

Player* Game::getPlayer() const { return _player; }
Player* Game::getEnemy() const { return _enemy; }