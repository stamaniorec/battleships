#pragma once

#include "Player.h"

class Game
{
	Player* _player;
	Player* _enemy;

	void init();
	void render() const;
	void renderPlayerStats(const Player& player) const;
	void renderPlayerBoard(const Board& board) const;
	void renderEnemyBoard(const Board& board) const;
	void renderSeparator() const;
public:
	void run();

	Game();
	~Game();
};