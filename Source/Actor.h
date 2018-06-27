#pragma once
#include "GameObject.h"

class Actor : public GameObject
{
public:
	Actor() = default;
	~Actor() = default;

	int getHealth() const		{ return health; }
	int getMaxHealth() const	{ return maxHealth; }
	int getArmour() const		{ return armour_rating; }
	int getAttack() const		{ return attack_rating; }

	bool isAlive() const;

	virtual std::string getHealthAsString() const;

	virtual int attack(Actor* obj) const;
	virtual int defend(int dmg);

protected:
	int health = 10;
	int maxHealth = 10;
	int armour_rating = 0;
	int attack_rating = 6;
};
