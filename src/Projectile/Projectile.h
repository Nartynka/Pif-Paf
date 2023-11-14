#pragma once
#include "..\Vec2.h"

class Projectile
{
public:
	Projectile();
	~Projectile();
	void Draw();
private:
	Vec2 size;
	Vec2 position;
	float speed;
	float gravity;
};