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
	void renderEnemyBoardWithRevealedAdjacent(const Board& board, const ShipPosition& position) const;

	bool _playedWithCruiserShip;
	bool _hasDestroyerShield;
	bool _playedWithSubmarineShip;

	void recoverCruiserHealth();
public:
	void run();

	void playWithBattleShip();
	void playWithCarrierShip();
	void playWithCruiserShip();
	void playWithDestroyerShip();
	void playWithSubmarineShip();

	Game();
	~Game();
};