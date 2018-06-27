#pragma once
#include "Panel.h"
#include <memory>

namespace ASGE
{
	class Renderer;
}

class MapPanel: public UIPanel
{

public:
	virtual void render(std::shared_ptr<ASGE::Renderer> renderer) override;
};