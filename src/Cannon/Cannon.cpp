#include "Cannon.h"
#include "../Render/Render.h"
#include "../Globals.h"
#include "../Projectile/Projectile.h"

#include <SDL_stdinc.h>

Cannon::Cannon()
{
	CreateTexture("res/Cannon.png", &texture, size);
	position = { 70.f, GROUND_LEVEL - size.y / 3 };
	rotation_point = { 0, size.y / 2 };
}

Cannon::~Cannon() = default;

void Cannon::Draw()
{
	DrawObject(texture, size, position, rotation, rotation_point);
}

void Cannon::Shoot()
{
	Bullets.push_back(new Projectile(position, 10, 10, 10));
}

void Cannon::rotate(double new_rotation)
{
	rotation = SDL_clamp(new_rotation, -90, 0);
}
