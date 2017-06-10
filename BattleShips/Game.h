#pragma once

class AIController;
class GameRenderer;

#include "Player.h"
#include "AIController.h"
#include "GameRenderer.h"

class Game
{
	Player* _player;
	Player* _enemy;
	AIController* _enemyController;
	GameRenderer* _gameRenderer;

	Ship* _lastPlayedWith;

	bool _isGameOver;

	void init();

	void playerTurn();
	void enemyTurn();

	Ship* chooseShipToPlayWith();
	const BoardPosition& chooseTarget();

	BoardPosition shoot();
public:
	void run();

	static const int NUM_SHIPS;
	static const char SHIP_LETTERS[];

	void playWithBattleShip();
	void playWithCarrierShip();
	void playWithCruiserShip();
	void playWithDestroyerShip();
	void playWithSubmarineShip();

	bool hasSeventyPercentChanceOfMissing() const;
	bool hasDestroyerShield() const;
	bool hasCruiserRecoveryEnabled() const;

	void recoverCruiserHealth();

	Player* getPlayer() const;
	Player* getEnemy() const;

	Game();
	~Game();
};