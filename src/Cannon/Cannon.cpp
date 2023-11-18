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
	projectile_spawn_point = { position.x + rotation_point.x + size.x - rotation * 2.f, position.y + rotation_point.y - rotation * 2.f};
	Bullets.push_back(new Projectile(projectile_spawn_point, 10, 10, 10, 1, rotation));
}

void Cannon::IncreaseRotation(float by_rotation)
{
	rotation = SDL_clamp(rotation+by_rotation, 0, 90);
}

void Cannon::IncreaseVelocity(float by_vel)
{
	initial_velocity = SDL_clamp(rotation + by_vel, 0, 100);
}

void Cannon::IncreaseGravity(float by_g)
{
	graivty = SDL_clamp(rotation + by_g, 0, 100);
}

void Cannon::IncreaseAirDrag(float by_ad)
{
	air_drag = SDL_clamp(rotation + by_ad, 0, 100);
}

int Cannon::GetRotation()
{
	return (int)rotation;
}
int Cannon::GetVelocity()
{
	return (int)initial_velocity;
}
int Cannon::GetGravity()
{
	return (int)graivty;
}
int Cannon::GetAirDrag()
{
	return (int)air_drag;
}