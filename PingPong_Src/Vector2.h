#pragma once
#include <iostream>
struct Vector2
{
	constexpr Vector2(void) : x(0), y(0) {}
	constexpr Vector2(float xVal, float yVal) : x(xVal), y(yVal) {}
	float x;
	float y;

	Vector2 Normalised() const 
	{
		Vector2 temp(x, y);
		temp.Normalise();
		return temp;
	}

	void Normalise() 
	{
		float length = Length();

		if (length != 0.0f) {
			length = 1.0f / length;
			x = x * length;
			y = y * length;
		}
	}

	float	Length() const 
	{
		return sqrt((x * x) + (y * y));
	}

	inline Vector2  operator+(const Vector2& a) const 
	{
		return Vector2(x + a.x, y + a.y);
	}

	inline Vector2  operator-(const Vector2& a) const 
	{
		return Vector2(x - a.x, y - a.y);
	}

	inline friend std::ostream& operator<<(std::ostream& o, const Vector2& v) 
	{
		o << "Vector2(" << v.x << "," << v.y << ")" << std::endl;
		return o;
	}

	inline constexpr void operator+=(const Vector2& a) 
	{
		x += a.x;
		y += a.y;
	}

	inline void operator-=(const Vector2& a) 
	{
		x -= a.x;
		y -= a.y;
	}

	inline Vector2  operator*(float a)	const 
	{
		return Vector2(x * a, y * a);
	}
};

