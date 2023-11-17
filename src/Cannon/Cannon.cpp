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
		if (!bullet->CheckScreenBounds())
			bullet->Draw();
		else
		{
			delete bullet;
			auto a = std::find(Bullets.begin(), Bullets.end(), bullet);
			Bullets.erase(a);
		}
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
	Bullets.push_back(new Projectile(projectile_pos, 10, 10, 10, 1, rotation));
}

void Cannon::ChangeRotation(float new_rotation)
{
	rotation = SDL_clamp(new_rotation, 0, 90);
}

void Cannon::ChangeVelocity(float new_vel)
{
	initial_velocity = SDL_clamp(new_vel, 0, 100);
}

void Cannon::ChangeGravity(float new_g)
{
	graivty = SDL_clamp(new_g, 0, 100);
}

void Cannon::ChangeAirDrag(float new_ad)
{
	air_drag = SDL_clamp(new_ad, 0, 100);
}
