#include <stdexcept>
#include "ShipTurnVerifier.h"

ShipTurnVerifier::ShipTurnVerifier()
{
	for (int i = 0; i < 5; i++)
	{
		_hasPlayedWith[i] = false;
	}
}

void ShipTurnVerifier::playWith(Ship* ship)
{
	int index = mapLetterToIndex(ship->getLetter());
	_hasPlayedWith[index] = true;
	
	_queue.push(index);

	if (_queue.size() >= 5)
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
	if (letter == 'B') return 0;
	else if (letter == 'C') return 1;
	else if (letter == 'R') return 2;
	else if (letter == 'D') return 3;
	else if (letter == 'S') return 4;
	else throw std::runtime_error("Invalid letter");
}