#pragma once

#include "Game.h"

class GameRenderer
{
	Game& _game;

	void renderPlayerStats(const Player& player) const;
	void renderPlayerBoard(const Board& board) const;
	void renderEnemyBoard(const Board& board) const;
	void renderSeparator() const;
public:
	GameRenderer(Game& game);

	void render() const;
	void renderShipChoicePrompt() const;
	void renderEnemyBoardWithRevealedAdjacent(const Board& board, const BoardPosition& position) const;

	static void waitToContinue();
	static void clearScreen();
};