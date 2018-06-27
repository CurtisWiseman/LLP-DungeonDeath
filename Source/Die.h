#pragma once
class Die
{
public:
	Die() = delete;
	Die(int sides);

	int rollDie();

private:
	int sides = 0;
};