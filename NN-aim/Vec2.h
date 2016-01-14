#pragma once

struct Vector2
{
	float x, y;
	Vector2() : x(0.f), y(0.f) {}
	Vector2(const float _x, const float _y) : x(_x), y(_y) {}

	inline int getIntX()
	{
		return static_cast<int>(x + 0.5f);
	}

	inline int getIntY()
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
};