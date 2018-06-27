#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Enemy.h"

class Room
{
	friend class Dungeon;
	struct RoomLink
	{
		Room* room = nullptr;
		std::string description = "Dead End";
	};

public:
	enum Direction
	{
		NORTH = 0,
		EAST = 1,
		SOUTH = 2,
		WEST = 3
	};
	Room();
	Room(Room&& rhs);
	Room& operator=(Room&& rhs);

	~Room();
	std::string getName();
	std::string getDescription();
	const std::string getRoomLinkDescription(Direction dir) const;
	const RoomLink& getRoomLink(Direction dir) const;
	void setEnemy(Enemy* en);
	void setEnemy(std::unique_ptr<Enemy>&& en);
	Enemy* getEnemy();
	const Enemy* getEnemy() const;

private:
	std::string name;
	std::string description;
	std::vector<RoomLink> roomLinks;
	std::unique_ptr<Enemy> enemy;
};