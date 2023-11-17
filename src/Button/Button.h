#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Vec2.h"
#include <functional>

struct SDL_Rect;
union SDL_Event;

class Button
{
public:
	Button(Vec2 size, Vec2 position, const char* btn_text, std::function<void()> callback);
	~Button();

	void Draw();
	void HandleInput(SDL_Event& e);
private:
	Vec2 size;
	Vec2 position;
	const char* text;
	std::function<void()> OnClick;
	bool is_hovering = false;
};