#include "Cannon.h"
#include "../Render/Render.h"
#include "../Globals.h"
#include "../Projectile/Projectile.h"

#include <SDL_stdinc.h>
#include <SDL_pixels.h>

Cannon::Cannon()
{
	CreateTexture("res/Cannon.png", &texture, size);
	CreateTexture("res/Wheels.png", &wheels_texture, wheels_size);
	position = { 50.f, GROUND_LEVEL - size.y / 2 };
	rotation_point = { 0, size.y / 2 };
	wheels_position = {position.x - 50, position.y + 30};
}

Cannon::~Cannon() = default;

void Cannon::Draw()
{
	DrawObject(wheels_texture, wheels_size, wheels_position);
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
	projectile_spawn_point = { position.x + rotation_point.x + size.x - rotation * 1.5f, position.y + rotation_point.y - rotation};
	Bullets.push_back(new Projectile(projectile_spawn_point, 10, initial_velocity, gravity, air_drag, rotation));
}

void Cannon::IncreaseRotation(float by_rotation)
{
	rotation = SDL_clamp(rotation + by_rotation, 0, 90);
}

void Cannon::IncreaseVelocity(float by_vel)
{
	initial_velocity = SDL_clamp(initial_velocity + by_vel, 0, 999);
}

void Cannon::IncreaseGravity(float by_g)
{
	gravity = SDL_clamp(gravity + by_g, 0, 999);
}

void Cannon::IncreaseAirDrag(float by_ad)
{
	air_drag = SDL_clamp(air_drag + by_ad, 0, 999);
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
	return (int)gravity;
}
int Cannon::GetAirDrag()
{
	return (int)air_drag;
}

int Cannon::GetBulletsCount()
{
	return (int)Bullets.size();
}

void Cannon::DrawStats()
{

	float angle = -rotation * M_PI / 180.0;

	// calculate the time spend in air
	float time = -(2 * initial_velocity * sin(angle)) / gravity;
	// calculate the distance traveled by the bullet
	float distance = -(initial_velocity * initial_velocity * sin(2 * angle)) / gravity;

	sprintf_s(time_buffer, "%f", time);
	sprintf_s(distance_buffer, "%f", distance);

	QueueText("Time spend in air: ", { 20, 20 }, { 150, 150, 150, 150 }, true);
	QueueText("Distance traveled: ", { 20, 50 }, { 150, 150, 150, 150 }, true);

	if (GetBulletsCount() > 0)
	{
		return;
	}

	QueueText(time_buffer, { 270, 20 }, { 150, 150, 150, 150 });
	QueueText(distance_buffer, { 270, 50 }, { 150, 150, 150, 150 });
}
