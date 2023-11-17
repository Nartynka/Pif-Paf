#include "Projectile.h"

#include "../Render/Render.h"
#include <cmath>
#include <stdio.h>
#include "..\Globals.h"

constexpr float M_PI = 3.14159265358979323846264338327950288f;

Projectile::Projectile(Vec2 position, int radius, float initial_velocity, float gravity, float air_drag, float angle)
{
	this->radius = radius;

	this->position = position;
	this->initial_velocity= initial_velocity;
	this->gravity = { 0, gravity };
	this->air_drag = { air_drag, 0 };

	// convert degrees to radians
	// it's signed because we rotate the cannon counterclockwise
	this->angle = -angle * M_PI / 180.0;

	// move projectile up according to angle of the cannon
	velocity.x = initial_velocity * cos(this->angle);
	velocity.y = initial_velocity * sin(this->angle);
}

Projectile::~Projectile() = default;

void Projectile::Draw()
{
	DrawCircle(position, radius);
}

void Projectile::Move(float dt)
{
	// calculate time spend in air
	static float time = 0;
	if(position.y < GROUND_LEVEL)
		time = (2 * velocity.y * sin(angle)) / gravity.y;

	printf("time: %f\n", -time);


	//auto b = (const char*)&time;
	//auto b = (const char*)&time;

	// apply forces
	velocity.y += gravity.y * dt;
	velocity -= air_drag * dt;

	position += velocity;
}

bool Projectile::CheckScreenBounds()
{
	if (position.x + size.x < 0 || position.x > SCREEN_WIDTH || position.y < 0 || position.y > SCREEN_HEIGHT)
	{
		return true;
	}

	return false;
}
