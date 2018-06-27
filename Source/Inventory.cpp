#include "Inventory.h"
#include <sstream>

Inventory::Inventory()
{
	//std::unique_ptr<Item> temp = std::make_unique<Item>();
	//items.push_back(std::move(temp));
}

void Inventory::addItem(std::unique_ptr<Item>&& _item)
{
	items.push_back(std::move(_item));
}

std::string Inventory::getRenderString()
{
	if (items.size() > 0)
	{
		std::stringstream ss;
		for (auto& item : items)
		{
			ss << item.get()->getDescription();
		}
		return ss.str().c_str();
	}
	return "No items in inventory.";
}