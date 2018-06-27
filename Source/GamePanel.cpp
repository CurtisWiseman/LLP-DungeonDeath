#include "GamePanel.h"
#include <Engine/Renderer.h>
#include <string>
#include <sstream>

constexpr int LENGTH = 27;
GamePanel::GamePanel()
{}

void GamePanel::render(std::shared_ptr<ASGE::Renderer> renderer)
{
	std::string out;
	for (auto& str:output)
	{
		out.append(str);
		if (str.back()!='\n')
		{
			out.append("\n");
		}
	}
	UIPanel::render(renderer);
	renderer->renderText(
		out.c_str(),
		getPosX()+18, getPosY()+18, ASGE::COLOURS::GHOSTWHITE);
}

void GamePanel::addOutput(std::string && str)
{
	static const auto max_length = 45;

	if (str.length()>max_length)
	{
		std::stringstream ss(str);
		std::string to;
		std::string strs[100];
		int counter = 0;

		while (std::getline(ss, to, '\n'))
		{
			if (to.length()>max_length)
			{
				for (unsigned i = 0; i < str.length(); i += max_length)
				{
					auto sub = to.substr(i, max_length);

					if (sub.front()==' ')
					{
						sub.erase(sub.begin());
					}

					if (i+max_length<str.length()&&
						sub.back()!=' '&&
						sub.back()!=','&&
						sub.back()!='.')
					{
						sub.append("-");
					}

					strs[counter++] = sub;
				}
			}
			else
			{
				strs[counter++] = std::move(to);
			}
		}

		for (int i = 0; i < counter; ++i)
		{
			output.push_back(std::move(strs[i]));
		}
	}

	else
	{
		output.push_back(str);
	}

	while (output.size() > LENGTH)
	{
		output.pop_front();
	}
}
