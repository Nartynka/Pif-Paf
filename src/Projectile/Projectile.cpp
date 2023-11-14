#include "Projectile.h"

#include "../Render/Render.h"

Projectile::Projectile(Vec2 position, int radius, float speed, float gravity)
{
	this->position = position;
	this->speed = speed;
	this->gravity = gravity;
	this->radius = radius;
}

Projectile::~Projectile() = default;

void Projectile::Draw()
{
	DrawCircle(position, radius);
}
