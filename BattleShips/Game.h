#pragma once

#include "Player.h"

class Game
{
	Player* _player;
	Player* _enemy;

	bool _isGameOver;

	void init();

	void playerTurn();
	void enemyTurn();

	Ship* chooseShipToPlayWith() const;
	const ShipPosition& chooseTarget() const;

	void render() const;
	void renderPlayerStats(const Player& player) const;
	void renderPlayerBoard(const Board& board) const;
	void renderEnemyBoard(const Board& board) const;
	void renderSeparator() const;

	void renderShipChoicePrompt() const;
public:
	void run();

	Game();
	~Game();
};