# battleships

A console game written in C++ for the OOP course at the Faculty of Math and Informatics (Sofia University).

The classical rules of the game can be found [here](https://en.wikipedia.org/wiki/Battleship).

The player plays against an AI. Both have a board with 5 ships placed on each. Each ship has a different size and a different number of health points. Each ship has a special ability they can use on each turn:
  - BattleShip - Adjacent fields are revealed
  - CarrierCruiser - Shoots one more time
  - CruiserShip - Recovers 1 health point unless hit or sunk
  - DestroyerShip - Activates protection shield which protects it from enemy shots
  - SubmarineShip - 70% chance of the AI missing its next shot

Each player chooses a position on the board and executes a shot on each turn.

The game continues until one of the players loses all of their ships.

A ship cannot be used again unless all other ships have been used, i.e. there's queue.
