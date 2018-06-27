#pragma once
#include <string>
#include <atomic>
#include <map>

enum class GameAction
{
	INVALID = -1,
	NONE = 0,
	ATTACK,
	NORTH,
	SOUTH,
	EAST,
	WEST,
	INVENTORY,
	PRINT_HELP
};

enum class Direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

namespace ActionStringLiterals
{
	const std::string attack = "ATTACK";
	const std::string north = "NORTH";
	const std::string south = "SOUTH";
	const std::string east = "EAST";
	const std::string west = "WEST";
	const std::string inventory = "INVENTORY";
	const std::string help = "HELP";
}

const std::map<const std::string, const std::string> help_strings
{
	{ ActionStringLiterals::attack,		"Attack the enemy" },
	{ ActionStringLiterals::north,		"Move to the north" },
	{ ActionStringLiterals::south,		"Move to the south" },
	{ ActionStringLiterals::east,		"Move to the east" },
	{ ActionStringLiterals::west,		"Move to the west" },
	{ ActionStringLiterals::inventory,	"Check your inventory" }
};

const std::map<const std::string, const GameAction>actions
{
	{ ActionStringLiterals::attack,		GameAction::ATTACK },
	{ ActionStringLiterals::north,		GameAction::NORTH },
	{ ActionStringLiterals::south,		GameAction::SOUTH },
	{ ActionStringLiterals::east,		GameAction::EAST },
	{ ActionStringLiterals::west,		GameAction::WEST },
	{ ActionStringLiterals::inventory,	GameAction::INVENTORY }
};

extern std::atomic<GameAction> game_action;