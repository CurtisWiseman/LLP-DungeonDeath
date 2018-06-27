#include "Key.h"

std::string Key::getDescription() const
{
	return "A key, for unlocking with.";
}

std::string Key::getRenderString() const
{
	return "0--->";
}