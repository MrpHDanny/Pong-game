#pragma once
#include "GameObject.h"

class Ball : public GameObject
{
public:

	Ball(Vector2 pos, int r, SDL_Color color);

	void updateObject(SDL_Renderer* game_renderer) override;
	void drawSelf(SDL_Renderer* renderer) override;
	
	void inverseDirection_y();	// Change y direction
	void inverseDirection_x();  // Change x direction
	
protected:
	SDL_Color renderBodyColor;
	int radius;
	int speed = 3;
};

