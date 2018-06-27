#include "Room.h"
#include "EnemyType.h"

Room::Room() : enemy(nullptr)
{
	roomLinks = { 4, RoomLink() };
}


Room::Room(Room&& rhs) : 
	name(rhs.name), 
	description(rhs.description), 
	roomLinks(rhs.roomLinks), 
	enemy(std::move(rhs.enemy))
{
	rhs.name = "";
	rhs.description = "";
	rhs.roomLinks.clear();
	rhs.enemy.release();
}

Room& Room::operator=(Room&& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	name = "";
	description = "";
	roomLinks.clear();
	enemy.release();

	name = rhs.name;
	description = rhs.description;
	roomLinks = rhs.roomLinks;
	enemy = std::move(rhs.enemy);

	return *this;
}

Room::~Room()
{

}

std::string Room::getName()
{
	return name;
}

std::string Room::getDescription()
{
	return description;
}

const std::string Room::getRoomLinkDescription(Direction dir) const
{
	return roomLinks[dir].description;
}

const Room::RoomLink& Room::getRoomLink(Direction dir) const
{
	return roomLinks[dir];
}

void Room::setEnemy(Enemy* en)
{
	enemy.reset(en);
}

void Room::setEnemy(std::unique_ptr<Enemy>&& en)
{
	enemy = std::move(en);
}

Enemy* Room::getEnemy()
{
	return &*enemy;
}

const Enemy* Room::getEnemy() const
{
	return &*enemy;
}