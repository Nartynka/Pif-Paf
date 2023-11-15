#include "Projectile.h"

#include "../Render/Render.h"

Projectile::Projectile(Vec2 position, int radius, float speed, float gravity, float air_drag)
{
	this->position = position;
	this->speed = speed;
	this->gravity = gravity;
	this->radius = radius;
	this->air_drag = air_drag;
}

Projectile::~Projectile() = default;

void Projectile::Draw()
{
	DrawCircle(position, radius);
}

void Projectile::Move(float dt)
{
	velocity.x = speed * dt;
	air_drag += gravity * dt;
	velocity.y = air_drag * dt;
	position += velocity;

}
