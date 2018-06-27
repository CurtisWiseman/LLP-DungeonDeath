#include "Player.h"
#include <Engine/Renderer.h>
#include <sstream>

#include "Key.h"

Player::Player(PlayerClass c)
	: player_class(c)
{
	switch (player_class)
	{

	case PlayerClass::WIZARD:
	{
		strength = 5;
		dexterity = 10;
		intelligence = 15;
		luck = 10;
		maxMana = 100;
		break;
	} 

	case PlayerClass::BARBARIAN:
	{
		strength = 15;
		dexterity = 10;
		intelligence = 5;
		luck = 5;
		maxMana = 0;
		break;
	} 

	case PlayerClass::ROGUE:
	{
		strength = 10;
		dexterity = 15;
		intelligence = 10;
		luck = 10;
		maxMana = 0;
		break;
	}

	}
	mana = maxMana;

	inventory = std::make_unique<Inventory>();
	inventory->addItem(std::make_unique<Key>());
}

Player::~Player()
{
	delete avatar;
}

void Player::loadAvatar(std::shared_ptr<ASGE::Renderer> renderer)
{
	avatar = renderer->createSprite();
	avatar->loadTexture("..\\..\\Resources\\Textures\\avatar");
	avatar->size[0] = 92;
	avatar->size[1] = 92;
}

ASGE::Sprite * Player::getAvatar()
{
	return avatar;
}

std::string Player::getManaAsString() const
{
	std::stringstream ss;
	/*
	for (int i = 0; i < mana; i += 5)
	{
		ss << '#';
	}
	*/
	ss << mana;
	return ss.str().c_str();
}

std::string Player::getRenderString() const
{
	return "Error: Player render string";
}

std::string Player::getDescription() const
{
	return player_description;
}

std::string Player::getInventoryAsString() const
{
	return inventory.get()->getRenderString();
}

void Player::setRoom(Room* rm)
{
	room = rm;
}