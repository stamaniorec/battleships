#include <iostream>
#include "Game.h"
#include "BattleShip.h"
#include "CarrierShip.h"
#include "CruiserShip.h"
#include "DestroyerShip.h"
#include "SubmarineShip.h"

using namespace std;

Game::Game()
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

	render();
}

void Game::init()
{
	_player = new Player("Player");
	_enemy = new Player("Enemy");

	_player->generateShips(); // TODO: get it from UI
	_enemy->generateShips();
}

void Game::render() const
{
	renderPlayerStats(*_enemy);
	renderPlayerBoard(_enemy->getBoard());
	renderSeparator();
	renderEnemyBoard(_player->getBoard());
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
				cout << ".";
			}
			else if (board.at(i, j) == MISSED)
			{
				cout << "~";
			}
			else if (board.at(i, j) == HIT)
			{
				cout << "X";
			}
			else if (board.at(i, j) == OCCUPIED)
			{
				Ship* ship = board.getShipAt(i, j);
				if (!ship)
				{
					// TODO throw exception
				}

				cout << ship->getLetter();
			}

			cout << " ";
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
				cout << ".";
			}
			else if (board.at(i, j) == MISSED)
			{
				cout << "~";
			}
			else if (board.at(i, j) == HIT)
			{
				cout << "X";
			}
			else if (board.at(i, j) == OCCUPIED)
			{
				cout << ".";
			}

			cout << " ";
		}
		cout << endl;
	}
}

void Game::renderSeparator() const
{
	cout << "-------------------" << endl;
	cout << "-------------------" << endl;
}