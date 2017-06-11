#include "GameRenderer.h"
#include "GameConfig.h"
#include "BoardCellState.h"

GameRenderer::GameRenderer(Game& game) : _game(game)
{
}

void GameRenderer::render() const
{
	renderPlayerStats(*_game.getEnemy());
	//renderPlayerBoard(_game.getEnemy()->getBoard());
	renderEnemyBoard(_game.getEnemy()->getBoard());
	renderSeparator();
	renderPlayerBoard(_game.getPlayer()->getBoard());
	renderPlayerStats(*_game.getPlayer());
}

void GameRenderer::renderPlayerStats(const Player& player) const
{
	cout << "Player: " << player.getName() << "; Score: " << player.getScore() << endl;
}

void GameRenderer::renderPlayerBoard(const Board& board) const
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

void GameRenderer::renderEnemyBoard(const Board& board) const
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

void GameRenderer::renderSeparator() const
{
	cout << FIELD_SEPARATOR_STRING << endl;
	cout << FIELD_SEPARATOR_STRING << endl;
}

void GameRenderer::renderEnemyBoardWithRevealedAdjacent(const Board& board, const BoardPosition& position) const
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
					cout << REVEALED_SHIP_POSITION_CHAR;
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

void GameRenderer::clearScreen()
{
	system("cls");
}

void GameRenderer::waitToContinue()
{
	cout << "Press a key to continue..." << endl;
	cout << PROMPT;

	cin.get();
	cin.clear();
}

void GameRenderer::renderShipChoicePrompt() const
{
	cout << "Available ships: " << endl;
	cout << endl;

	Ship** allPlayerShips = _game.getPlayer()->getBoard().getShips();

	for (int i = 0; i < NUM_SHIPS; i++)
	{
		Ship* ship = allPlayerShips[i];

		if (ship->isAlive() && _game.getPlayer()->canPlayWith(ship))
		{
			cout << ship->getName() << "(" << ship->getLetter() << "), " << endl;
		}
	}

	cout << endl;
	cout << "Enter letter for ship to play with..." << endl;
}