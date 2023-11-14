#pragma once

#include "../Vec2.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Draw();
protected:
	struct SDL_Texture* texture;
	Vec2 size;
	Vec2 position;
};