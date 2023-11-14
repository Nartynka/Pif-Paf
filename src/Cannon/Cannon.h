#pragma once

#include "../Vec2.h"

class Cannon
{
public:
	Cannon();
	~Cannon();
	void Draw();
	void Shoot();
	void rotate(double new_rotation);

private:
	struct SDL_Texture* texture;
	Vec2 size;
	Vec2 position;
	Vec2 rotation_point;
	double rotation = 0.0;
	int projectile_radius = 10;
};