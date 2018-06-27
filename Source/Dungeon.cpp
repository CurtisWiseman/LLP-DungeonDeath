#include "Dungeon.h"
#include "Room.h"

void Dungeon::create()
{
	const int num_rooms = 5;
	rooms.reserve(num_rooms);
	Room temp[num_rooms];
	for (auto& rm : temp)
	{
		rooms.push_back(std::move(rm));
	}

	Room& room1 = rooms[0];
	Room& room2 = rooms[1];

	room1.name = "Grand Dad's Room";
	room1.description = "A grand room, fittingly";
	room1.roomLinks[Room::Direction::NORTH].description = "A chilly room lies to the north";
	room1.roomLinks[Room::Direction::NORTH].room = &room2;

	room2.name = "Nozoomy's Room";
	room2.description = "A smol room";
	room2.roomLinks[Room::Direction::SOUTH].description = "A much grander room lies south";
	room2.roomLinks[Room::Direction::SOUTH].room = &room1;
}

Room* Dungeon::getRoom(int idx)
{
	return &rooms[idx];
}

Dungeon::~Dungeon()
{
	
}