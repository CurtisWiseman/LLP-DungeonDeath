#pragma once
#include "GameObject.h"

class Item : public GameObject
{
public:
	virtual std::string getDescription() const;
	virtual std::string getRenderString() const;
};