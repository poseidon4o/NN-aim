#pragma once
#include <cmath>

struct Vector2
{
	float x, y;
	Vector2() : x(0.f), y(0.f) {}
	Vector2(const float _x, const float _y) : x(_x), y(_y) {}

	inline int getIntX() const
	{
		return static_cast<int>(x + 0.5f);
	}

	inline int getIntY() const
	{
		return static_cast<int>(y + 0.5f);
	}

	inline Vector2 operator+(const Vector2& r)
	{
		return Vector2(x + r.x, y + r.y);
	}

	inline Vector2 operator-(const Vector2& r)
	{
		return Vector2(x - r.x, y - r.y);
	}

	inline Vector2 operator*(const float r)
	{
		return Vector2(x * r, y * r);
	}

	inline Vector2 operator/(const float r)
	{
		return Vector2(x / r, y / r);
	}

	inline Vector2& operator+=(const Vector2& r)
	{
		x += r.x;
		y += r.y;
		return *this;
	}

	inline Vector2& operator-=(const Vector2& r)
	{
		x -= r.x;
		y -= r.y;
		return *this;
	}

	inline Vector2& operator*=(const float r)
	{
		x *= r;
		y *= r;
		return *this;
	}

	inline Vector2& operator/=(const float r)
	{
		x /= r;
		y /= r;
		return *this;
	}

	inline float length()
	{
		return sqrt(x * x + y * y);
	}

	inline Vector2& normalize()
	{
		float len = length();
		x /= len;
		y /= len;
		return *this;
	}

	float dotProduct(const Vector2& right)
	{
		return x * right.x + y * right.y;
	}

	//returns new vector perpendiculiar to this
	Vector2 perp()
	{
		return Vector2(-y, x);
	}
};