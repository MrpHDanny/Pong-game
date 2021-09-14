#pragma once
#include "Vector2.h"
#include "Rigidbody.h"

class CollisionVolume
{
public:
	CollisionVolume();

	virtual bool isCollision(CollisionVolume* s);		// Not making this pure virtual as we'll be only ever be checking circle - rectangle collisions	
	
	Vector2 getPosition() const { return position; };
	Vector2 getCollisionNormal() const { return collision_normal; }
	
	void setPosition(const Vector2& newPosition) { position = newPosition;  };
	void setCollisionNormal(Vector2 norm) { collision_normal = norm; }
	
protected:
	Vector2 position;
	Vector2 collision_normal;

	Rigidbody* parentBody = nullptr;
};

