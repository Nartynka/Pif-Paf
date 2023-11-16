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
	DrawObject(texture, size, position, -rotation, rotation_point);
}

void Cannon::DrawProjectiles()
{
	for (Projectile* bullet : Bullets)
	{
		bullet->Draw();
	}
}

void Cannon::MoveProjectiles(float dt)
{
	for (Projectile* bullet : Bullets)
	{
		bullet->Move(dt);
	}
}

void Cannon::Shoot()
{
	Vec2 projectile_pos = { position.x + 170, position.y - 60 };
	Bullets.push_back(new Projectile(projectile_pos, 10, 30, 50, 10, rotation));
}

void Cannon::rotate(double new_rotation)
{
	rotation = SDL_clamp(new_rotation, 0, 90);
}
