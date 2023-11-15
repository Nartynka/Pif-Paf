#pragma once
#include "../GameObject/GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(Vec2 position, int radius, float speed, float gravity, float air_drag);
	~Projectile();

	void Draw() override;
	void Move(float dt);
private:
	Vec2 velocity = { 0.f, 0.f };
	float speed;
	float gravity;
	float air_drag;
	int radius;
};