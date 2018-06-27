#pragma once
#include "Panel.h"
#include <memory>
#include <string>
#include <deque>

namespace ASGE
{
	class Renderer;
}

class GamePanel : public UIPanel
{

public:
	GamePanel();
	~GamePanel() = default;
	virtual void render(std::shared_ptr<ASGE::Renderer> renderer) override;
	void addOutput(std::string&&);
private:
	std::deque<std::string> output;
};