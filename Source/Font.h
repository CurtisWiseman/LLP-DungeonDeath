#pragma once

struct Font
{
	Font(int idx, char* n, int ptm);

	int id = 0;
	int size = 0;
	char* name = "";

	// cheap 'n' nasty way to store fonts
	static Font*  fonts[5];
};