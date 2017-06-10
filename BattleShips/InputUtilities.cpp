#include <iostream>
#include <ctype.h>
#include "InputUtilities.h"
#include "GameConfig.h"

using namespace std;

char InputUtilities::enterLetter()
{
	char letter = 0;

	while (!isalpha(letter))
	{
		cout << PROMPT;

		cin.get(letter);

		if (letter == '\n')
		{
			continue;
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return letter;
}