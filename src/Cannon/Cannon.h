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

	void IncreaseRotation(float by_rotation);
	void IncreaseVelocity(float by_vel);
	void IncreaseGravity(float by_g);
	void IncreaseAirDrag(float by_ad);

	int GetRotation();
	int GetVelocity();
	int GetGravity();
	int GetAirDrag();

	int GetBulletsCount();

private:
	Vec2 rotation_point;
	Vec2 projectile_spawn_point;
	float rotation = 30.f;
	std::vector<class Projectile*> Bullets;

	SDL_Texture* wheels_texture;
	Vec2 wheels_size;
	Vec2 wheels_position;

	float initial_velocity = 10.f;
	float graivty = 10.f;
	float air_drag = 1.f;
};