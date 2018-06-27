#include "Panel.h"
#include <Engine/Renderer.h>
#include "Constants.h"

int UIPanel::getHeight() const 
{
	return height;
}

int UIPanel::getWidth() const 
{
	return width;
}

int UIPanel::getPosX() const 
{
	return x_pos;
}

int UIPanel::getPosY() const 
{
	return y_pos;
}

void UIPanel::setPosX(int x) 
{
	x_pos = x;
}

void UIPanel::setPosY(int y) 
{
	y_pos = y;
}

void UIPanel::setWidth(int w) 
{
	width = w;
}

void UIPanel::setHeight(int h) 
{
	height = h;
}

void UIPanel::render(std::shared_ptr<ASGE::Renderer> renderer)
{
	for (int row = 0; row < width; ++row)
	{
		for (int col = 0; col < height; ++col)
		{
			if (row == 0 || row == width - 1 || col == 0 || col == height - 1)
			{
				renderer->renderText("*", 
									 x_pos + (row * BORDER_CELL_WIDTH), 
									 y_pos + (col * BORDER_CELL_HEIGHT), 
									 ASGE::COLOURS::BISQUE);
			}
				
		}
	}
}