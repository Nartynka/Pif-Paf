#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Vec2.h"
#include <functional>

struct SDL_Rect;
union SDL_Event;

class Button
{
public:
	Button(Vec2 size, Vec2 position, std::function<void()> callback);
	~Button();

	void Draw();
	void HandleClick(SDL_Event& e);
private:
	Vec2 size;
	Vec2 position;
	std::function<void()> OnClick;
};