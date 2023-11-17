#include "Button.h"
#include "..\Render\Render.h"

#include <SDL.h>

Button::Button(Vec2 size, Vec2 position, const char* btn_text, std::function<void()> callback) : size(size), position(position), text(btn_text), OnClick(callback)
{
}

Button::~Button() = default;

void Button::Draw()
{
	SDL_Rect rect = { (int)position.x, (int)position.y, (int)size.x, (int)size.y };
	SDL_Color color = is_hovering ? SDL_Color({ 150, 150, 150, 255 }) : SDL_Color({255, 255, 255, 255});
	DrawFillRect(rect, (SDL_Color&&)color);
	DrawRect(rect, { 50, 50, 50, 255 });
	QueueText(text, { position.x + size.x / 2 - 6, position.y + size.y / 2 - 12}, true);
}

void Button::HandleInput(SDL_Event& e) {
	bool is_on_btn = false;
	if (e.type == SDL_MOUSEMOTION)
	{
		int mouse_x, mouse_y;

		SDL_GetMouseState(&mouse_x, &mouse_y);

		if (mouse_x >= position.x && mouse_x < position.x + size.x && mouse_y >= position.y && mouse_y < position.y + size.y) {
			is_hovering = true;
			is_on_btn = true;
		}
		else
		{
			is_hovering = false;
		}
	}
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
		if(is_on_btn)
			OnClick();
	}
	
}