#include "Button.h"
#include "..\Render\Render.h"

#include <SDL.h>

Button::Button(Vec2 size, Vec2 position, std::function<void()> callback) : size(size), position(position), OnClick(callback)
{
}

Button::~Button() = default;

void Button::Draw()
{
	SDL_Rect rect = { (int)size.x, (int)size.y, (int)position.x, (int)position.y };
	DrawRect(rect, {0, 0, 0, 255});
}

void Button::HandleClick(SDL_Event& e) {
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
		printf("handeee");
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		if (mouseX >= position.x && mouseX < position.x + size.x && mouseY >= position.y && mouseY < position.y + size.y) {
			printf("click!");
			OnClick();
		}
	}
}