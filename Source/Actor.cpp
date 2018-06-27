#include "Actor.h"
#include <sstream>
#include "Die.h"

bool Actor::isAlive() const
{
	if (this->health > 0)
	{
		return true;
	}
	return false;
}

std::string Actor::getHealthAsString() const
{
	std::stringstream ss;
	ss << this->health;

	return ss.str().c_str();
}

int Actor::attack(Actor* obj) const
{
	static Die die(attack_rating);
	auto dmg = die.rollDie();
	auto hitpoints = obj->defend(dmg);

	return hitpoints;
}

int Actor::defend(int dmg)
{
	dmg -= this->armour_rating;
	this->health -= dmg;
	if (this->health < 0)
	{
		this->health = 0;
	}

	return dmg;
}