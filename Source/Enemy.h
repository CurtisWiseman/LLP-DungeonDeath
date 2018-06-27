#pragma once
#include <memory>
#include "Actor.h"

class EnemyType;
class Player;

class Enemy : public Actor
{
public:
	friend class EnemyType;
	~Enemy() = default;

	int getHealth() const;

	virtual std::string getHealthAsString() const override;
	virtual std::string getRenderString() const override;
	virtual std::string getDescription() const override;
	virtual std::string Enemy::getDeadStr() const;
	virtual std::string Enemy::getAttackStr() const;

	EnemyType& type;

private:
	Enemy(EnemyType&);
};