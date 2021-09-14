#pragma once
#include "CollisionVolume.h"
#include "RectangleCollider.h"
#include <SDL.h>

class CircleCollider : public CollisionVolume
{
public:
	CircleCollider(unsigned int r, Vector2 pos, Rigidbody* rb);
	
	bool isCollision(RectangleCollider* s, SDL_Renderer* rend);
	
	int getRadius() const { return radius; };
	
protected:
	unsigned int radius;
};

