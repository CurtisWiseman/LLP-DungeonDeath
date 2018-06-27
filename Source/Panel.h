#pragma once
#include <memory>
namespace ASGE
{
	class Renderer;
}

class UIPanel
{

public:
	UIPanel() = default;
	virtual ~UIPanel() = default;
	virtual void render(std::shared_ptr<ASGE::Renderer> renderer);

	int  getHeight() const;
	int  getWidth()  const;
	int  getPosX()   const;
	int  getPosY()   const;
	
	void setPosX(int x);
	void setPosY(int y);
	void setWidth(int w);
	void setHeight(int h);

private:
	int x_pos  = 0;
	int y_pos  = 0;
	int height = 10;
	int width  = 10;
};