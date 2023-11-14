#pragma once

#include "../GameObject/GameObject.h"
#include <vector>

class Cannon : public GameObject
{
public:
	Cannon();
	~Cannon();
	void Draw() override;
	void Shoot();
	void rotate(double new_rotation);

private:
	Vec2 rotation_point;
	double rotation = 0.0;
	std::vector<class Projectile*> Bullets;
};