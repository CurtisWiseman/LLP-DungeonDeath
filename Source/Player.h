#pragma once
#include <Engine/Sprite.h>
#include "Actor.h"
#include "Inventory.h"

namespace ASGE {
	class Renderer;
	class Sprite;
}

class Room;

class Player : public Actor
{
public:

	enum class PlayerClass
	{
		BARBARIAN,
		ROGUE,
		WIZARD
	};

	Player(PlayerClass c);
	~Player();

	void loadAvatar(std::shared_ptr<ASGE::Renderer> renderer);
	ASGE::Sprite* getAvatar();

	int getXP() const			{ return experience; }
	int getStrength() const		{ return strength; }
	int getDexterity() const	{ return dexterity; }
	int getIntellect() const	{ return intelligence; }
	int getLuck() const			{ return luck; }
	int getMana() const			{ return mana; }
	int getMaxMana() const		{ return maxMana; }

	Room* getRoom() const		{ return room; }
	void setRoom(Room* rm);
	std::string getManaAsString() const;

	//inherited stuff
	std::string getRenderString() const override;
	std::string getDescription() const override;
	std::string getInventoryAsString() const;

private:
	
	PlayerClass player_class;
	ASGE::Sprite* avatar = nullptr;

	int experience = 0;
	int strength = 0;
	int dexterity = 0;
	int intelligence = 0;
	int luck = 0;
	int mana = 0;
	int maxMana;
	std::string player_description = "Yourself, a dungeon explorer";
	Room* room = nullptr;
	std::unique_ptr<Inventory> inventory;
};