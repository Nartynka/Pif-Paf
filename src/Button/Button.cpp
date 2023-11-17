#include "Button.h"
#include "..\Render\Render.h"

#include "SDL_image.h"
#include "SDL_rect.h"

Button::Button(Vec2 size, Vec2 position, void(*callback)) : size(size), position(position), callback(callback)
{
}

Button::~Button() = default;

void Button::Draw()
{
	SDL_Rect rect = { (int)size.x, (int)size.y, (int)position.x, (int)position.y };
	DrawRect(rect, {0, 0, 0, 255});
}