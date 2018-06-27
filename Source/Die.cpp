#include "Die.h"
#include <random>

Die::Die(int sideCount)
	:sides(sideCount)
{
	return;
}

int Die::rollDie()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> random(1, sides);

	return random(mt);
}