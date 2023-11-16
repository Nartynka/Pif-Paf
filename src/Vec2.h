#pragma once

struct Vec2
{
	float x;
	float y;

	void operator+=(Vec2 b)
	{
		x += b.x;
		y += b.y;
	}
	void operator-=(Vec2 b)
	{
		x -= b.x;
		y -= b.y;
	}

	Vec2 operator*(float b)
	{
		return { x * b, y * b };
	}
	Vec2 operator*(Vec2 b)
	{
		return { x * b.x, y * b.y };
	}

	Vec2 operator/(float b)
	{
		return { x / 2, y / 2 };
	}

	Vec2 operator-(float b)
	{
		return { x - b, y - b };
	}
	Vec2 operator-(Vec2 b)
	{
		return { x - b.x, y - b.y };
	}
	Vec2 operator-()
	{
		return { -x, -y };
	}
};