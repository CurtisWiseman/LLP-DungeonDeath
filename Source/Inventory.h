#pragma once
#include "Item.h"
#include <vector>
#include <memory>

class Inventory
{
public:
	Inventory();
	~Inventory() = default;
	void addItem(std::unique_ptr<Item>&& _item);
	std::string getRenderString();

private:
	std::vector<std::unique_ptr<Item>> items;
};