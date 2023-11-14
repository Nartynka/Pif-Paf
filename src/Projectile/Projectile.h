#pragma once
#include "../GameObject/GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(Vec2 position, int radius, float speed, float gravity);
	~Projectile();

	void Draw() override;
private:
	float speed;
	float gravity;
	int radius;
};