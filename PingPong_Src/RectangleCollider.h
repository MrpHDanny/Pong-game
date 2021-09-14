#pragma once
#include "CollisionVolume.h"

class RectangleCollider : public CollisionVolume
{
public:
	RectangleCollider(unsigned int w, unsigned int h, Vector2 pos, Rigidbody* rb);
	Vector2 getHalfSize() const { return Vector2( width / 2, height / 2 ); };
protected:
	unsigned int width;
	unsigned int height;
};

