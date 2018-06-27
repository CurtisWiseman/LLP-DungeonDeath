#pragma once
#include <vector>

class Room;
class Dungeon
{
public:
	Dungeon() = default;
	~Dungeon();

	void create();
	Room* getRoom(int idx);

private:
	//Room* rooms = nullptr;
	std::vector<Room> rooms;
};