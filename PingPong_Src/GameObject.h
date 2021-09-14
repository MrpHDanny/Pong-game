#pragma once
#include "Rigidbody.h"
#include "CollisionVolume.h"
#include <SDL.h>


class GameObject : public Rigidbody
{
public:
	GameObject();
	~GameObject();

	virtual void updateObject(SDL_Renderer* game_renderer) = 0;	// Update object physics
	virtual void drawSelf(SDL_Renderer* renderer) = 0;			// Render object onto game window
	
	void setCollider(CollisionVolume* c) { collider = c; };		
	
	CollisionVolume* getCollider() const { return collider; };

protected:
	CollisionVolume* collider;									// Physics collider
};

