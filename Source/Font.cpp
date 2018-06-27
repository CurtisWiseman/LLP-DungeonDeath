#include "Font.h"

Font::Font(int idx, char* n, int ptm)
	: id(idx), name(n), size(ptm)
{

}

// static variables for fonts
Font* Font::fonts[5] = { nullptr };

