#include <iostream>
#include "Game.h"

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

	_player->generateShips(); // get it from ui
	_enemy->generateShips();
}

void Game::render() const
{
	renderPlayerStats(*_enemy);
	renderBoard(_enemy->getBoard());
	renderSeparator();
	renderBoard(_player->getBoard());
	renderPlayerStats(*_player);
}

void Game::renderPlayerStats(const Player& player) const
{
	cout << "Player: " << player.getName() << "; Score: " << player.getScore() << endl;
}

void Game::renderBoard(const Board& board) const
{
	for (int i = 0; i < board.getSize(); i++)
	{
		for (int j = 0; j < board.getSize(); j++)
		{
			if (board.at(i, j) == 0)
			{
				cout << "0";
			}
			else
			{
				cout << "1";
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