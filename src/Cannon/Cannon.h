#pragma once

#include "../GameObject/GameObject.h"
#include <vector>

class Cannon : public GameObject
{
public:
	Cannon();
	~Cannon();
	void Draw() override;
	void DrawProjectiles();
	void MoveProjectiles(float dt);
	void Shoot();
	void ChangeRotation(float new_rotation);

	void ChangeVelocity(float new_vel);
	void ChangeGravity(float new_g);
	void ChangeAirDrag(float new_ad);

private:
	Vec2 rotation_point;
	double rotation = 0.0;
	std::vector<class Projectile*> Bullets;

	int initial_velocity = 10;
	float graivty = 10.f;
	float air_drag = 1.f;
};