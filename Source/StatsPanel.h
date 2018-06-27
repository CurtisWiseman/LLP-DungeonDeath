#pragma once
#include "Panel.h"
#include "Player.h"
#include <memory>

class Player;

class StatsPanel: public UIPanel
{
public:
	StatsPanel() = default;
	~StatsPanel();

	void init(Player* player);
	virtual void render(std::shared_ptr<ASGE::Renderer> renderer) override;

private:
	void renderStats(std::shared_ptr<ASGE::Renderer> renderer);
	void renderTitle(std::shared_ptr<ASGE::Renderer> renderer);
	void renderHealth(std::shared_ptr<ASGE::Renderer> renderer);

	Player* player_ptr = nullptr;
};