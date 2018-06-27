#pragma once
#include "Item.h"

class Key : public Item
{
public:
	std::string getDescription() const;
	std::string getRenderString() const;
};