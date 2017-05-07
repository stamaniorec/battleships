#pragma once

#include "Player.h"

class Game
{
	Player* _player;
	Player* _enemy;

	void init();
	void render() const;
	void renderPlayerStats(const Player& player) const;
	void renderBoard(const Board& board) const;
	void renderSeparator() const;
public:
	void run();

	Game();
	~Game();
};