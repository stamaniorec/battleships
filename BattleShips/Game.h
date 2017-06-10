#pragma once

#include "Player.h"

class Game
{
	Player* _player;
	Player* _enemy;

	bool _isGameOver;

	Ship* _lastPlayedWith;

	void init();

	void playerTurn();
	void enemyTurn();

	Ship* chooseShipToPlayWith();
	const BoardPosition& chooseTarget();

	char enterLetter() const;

	BoardPosition shoot();

	bool hasSeventyPercentChanceOfMissing() const;
	bool hasDestroyerShield() const;
	bool hasCruiserRecoveryEnabled() const;

	void recoverCruiserHealth();

	void waitToContinue() const;

	void render() const;
	void renderPlayerStats(const Player& player) const;
	void renderPlayerBoard(const Board& board) const;
	void renderEnemyBoard(const Board& board) const;
	void renderSeparator() const;

	void renderShipChoicePrompt() const;
	void renderEnemyBoardWithRevealedAdjacent(const Board& board, const BoardPosition& position) const;

	void clearScreen() const;

public:
	void run();

	static const int NUM_SHIPS;
	static const char* SHIP_LETTERS[];

	void playWithBattleShip();
	void playWithCarrierShip();
	void playWithCruiserShip();
	void playWithDestroyerShip();
	void playWithSubmarineShip();

	Game();
	~Game();
};