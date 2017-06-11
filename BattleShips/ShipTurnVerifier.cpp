#include <stdexcept>
#include "ShipTurnVerifier.h"

ShipTurnVerifier::ShipTurnVerifier()
{
	for (int i = 0; i < NUM_SHIPS; i++)
	{
		_hasPlayedWith[i] = false;
	}
}

void ShipTurnVerifier::playWith(Ship* ship)
{
	int index = mapLetterToIndex(ship->getLetter());
	_hasPlayedWith[index] = true;
	
	_queue.push(index);

	if (_queue.size() >= NUM_SHIPS)
	{
		int unmarkIndex = _queue.front();
		_queue.pop();
		_hasPlayedWith[unmarkIndex] = false;
	}
}

bool ShipTurnVerifier::canPlayWith(Ship* ship) const
{
	if (!ship)
	{
		return false;
	}

	return !_hasPlayedWith[mapLetterToIndex(ship->getLetter())];
}

int ShipTurnVerifier::mapLetterToIndex(char letter) const
{
	if (letter == BATTLE_SHIP_RENDER_LETTER) return 0;
	else if (letter == CARRIER_SHIP_RENDER_LETTER) return 1;
	else if (letter == CRUISER_SHIP_RENDER_LETTER) return 2;
	else if (letter == DESTROYER_SHIP_RENDER_LETTER) return 3;
	else if (letter == SUBMARINE_SHIP_RENDER_LETTER) return 4;
	else throw std::runtime_error("Invalid letter");
}