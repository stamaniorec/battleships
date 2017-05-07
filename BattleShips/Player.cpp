#include "Player.h"

Player::Player(char* name) : _name(name), _score(0) {}

Player::Player() : _score(0), _name(nullptr) {};

const Board& Player::getBoard() const
{
	return _board;
}

char* Player::getName() const
{
	return _name;
}

int Player::getScore() const
{
	return _score;
}

void Player::generateShips()
{

}