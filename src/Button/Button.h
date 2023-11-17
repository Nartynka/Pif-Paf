#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Vec2.h"

struct SDL_Rect;

class Button
{
public:
	Button(Vec2 size, Vec2 position, void(*callback));
	~Button();

	void OnClick();
	void Draw();
private:
	void(*callback);
	Vec2 size;
	Vec2 position;
};