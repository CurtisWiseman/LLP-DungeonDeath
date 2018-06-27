#pragma once
#include "Panel.h"
#include <memory>
#include <string>
namespace ASGE
{
	class Renderer;
}

class InputPanel : public UIPanel
{
public:
	InputPanel() = default;
	~InputPanel() = default;

	virtual void render(std::shared_ptr<ASGE::Renderer> renderer) override;
	void input(int key, int action);
	void action(std::string& input);

private:
	std::string str = "";
};