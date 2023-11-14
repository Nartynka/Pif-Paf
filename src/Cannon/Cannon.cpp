#include "Cannon.h"
#include "..\Render\Render.h"
#include "..\Globals.h"
#include "SDL_stdinc.h"

Cannon::Cannon()
{
	CreateTexture("res/Cannon.png", &texture, size);
	position = { 70.f, GROUND_LEVEL-size.y/3};
	rotation_point = { 0, size.y / 2 };
}

Cannon::~Cannon()
{

}

void Cannon::Draw()
{
	DrawObject(texture, size, position, rotation, rotation_point);
}

void Cannon::Shoot()
{
	DrawCircle({ (float)100, (float)100}, projectile_radius);
}

void Cannon::rotate(double new_rotation)
{
	rotation = SDL_clamp(new_rotation, -90, 0);
}
