#pragma once
#include "../GameObject/GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(Vec2 position, int radius, float initial_velocity, float gravity, float air_drag, float rotation);
	~Projectile();

	void Draw() override;
	void Move(float dt);
private:
	Vec2 velocity = { 0.f, 0.f };
	float initial_velocity;
	Vec2 gravity;
	Vec2 air_drag;

	int radius;
	float angle;
};