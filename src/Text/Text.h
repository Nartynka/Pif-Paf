#pragma once
#include "..\Vec2.h"

struct Text
{
	const char* text;
	Vec2 position;
	SDL_Color color;
	bool is_bold;
};