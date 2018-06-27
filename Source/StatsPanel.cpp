#include "StatsPanel.h"
#include "Player.h"

#include <Engine/Renderer.h>
#include <Engine/Sprite.h>
#include <string>
#include <stdio.h>

const std::string title =
R"(
STATS
)";

const std::string stats =
R"(
Strength     : [%02d/20]   Dexterity : [%02d/20]
Intelligence : [%02d/20]   Luck      : [%02d/20]
Experience   : %00000007d
)";

const std::string health =
R"(
Health : %00000000000000000000s/%3d
Mana   : %00000000000000000000s/%3d
)";

StatsPanel::~StatsPanel()
{
	
}

void StatsPanel::init(Player* player)
{
	this->player_ptr = player;
	auto avatar = player->getAvatar();
	if (avatar)
	{
		avatar->position[1] = getPosY() + 125;
		avatar->position[0] = getPosX() + 500;
	}

	return;
}

void StatsPanel::render(std::shared_ptr<ASGE::Renderer> renderer)
{
	UIPanel::render(renderer);
	renderTitle(renderer);
	renderStats(renderer);
	renderHealth(renderer);
}

void StatsPanel::renderTitle(std::shared_ptr<ASGE::Renderer> renderer)
{
	renderer->setFont(1);
	renderer->renderText(title.c_str(),
		getPosX() + 18,
		getPosY() + 2, ASGE::COLOURS::STEELBLUE);
}

void StatsPanel::renderStats(std::shared_ptr<ASGE::Renderer> renderer)
{
	auto avatar = player_ptr->getAvatar();
	avatar->render(renderer);

	renderer->setFont(0);
	auto size = stats.size();
	char* buff = new char[size];

	snprintf(buff,
		sizeof(char)*size,
		stats.c_str(),
		player_ptr->getStrength(),
		player_ptr->getDexterity(),
		player_ptr->getIntellect(),
		player_ptr->getLuck(),
		player_ptr->getXP());

	renderer->renderText(buff,
		getPosX() + 18,
		getPosY() + 50, ASGE::COLOURS::STEELBLUE);

	delete[] buff;

}

void StatsPanel::renderHealth(std::shared_ptr<ASGE::Renderer> renderer)
{
	renderer->setFont(0);
	auto size = health.size();

	char* buff = new char[size];
	snprintf(buff,
		sizeof(char)*size,
		health.c_str(),
		player_ptr->getHealthAsString().c_str(),
		player_ptr->getMaxHealth(),
		player_ptr->getManaAsString().c_str(),
		player_ptr->getMaxMana());

	renderer->renderText(buff,
		getPosX() + 18,
		getPosY() + 150, ASGE::COLOURS::STEELBLUE);

	delete[] buff;

}
