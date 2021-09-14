#pragma once
#include "Vector2.h"

class Rigidbody
{
public:
	Rigidbody();

	Vector2 getPosition() const { return position; }
	Vector2 getVelocity() const { return velocity; }
	Vector2 getDirection() const { return direction; }

	void setPosition(const Vector2& newPosition) { position = newPosition; };
	void setVelocity(const Vector2& newVelocity) { velocity = newVelocity; };
	void setDirection(const Vector2& newDirection) { direction = newDirection; };

protected:
	Vector2 position;
	Vector2 velocity;
	Vector2 direction;
};

