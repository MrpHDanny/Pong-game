#include "CircleCollider.h"
#include <math.h>

CircleCollider::CircleCollider(unsigned int r, Vector2 pos, Rigidbody* rb)
{
	setPosition(pos);
	radius = r;
	parentBody = rb;
}

bool CircleCollider::isCollision(RectangleCollider* rectangle_col, SDL_Renderer* game_renderer)
{

	float testX = this->getPosition().x;
	float testY = this->getPosition().y;

	// Circle
	int cx = this->getPosition().x;
	int cy = this->getPosition().y;
	int r = this->getRadius();

	// AABB
	int rw = rectangle_col->getHalfSize().x;
	int rh = rectangle_col->getHalfSize().y;
	int rx = rectangle_col->getPosition().x + rw;
	int ry = rectangle_col->getPosition().y + rh;

	// which edge is closest?
	if (cx < rx - rw) testX = rx - rw; // Test left edge
	else if (cx > rx + rw) testX = rx + rw; // Test right edge

	if (cy < ry - rh) testY = ry - rh; // Test bottom edge
	else if (cy > ry + rh) testY = ry + rh; // Test Top edge

	// get distance from closest edges
	int distX = cx - testX;
	int distY = cy - testY;
	float distance = sqrt(pow(distX, 2) + pow(distY, 2));


	// For debug purposes
	//SDL_SetRenderDrawColor(game_renderer, 255, 0, 0, 0);
	//SDL_RenderDrawLine(game_renderer, cx, cy, testX, testY);
	//SDL_SetRenderDrawColor(game_renderer, 0, 0, 255, 0);
	//SDL_RenderDrawLine(game_renderer, cx, cy, rx, ry);

	if (distance < r)
	{
		Vector2 closestPoint(testX, testY);
		Vector2 normal = (this->getPosition() - Vector2(rx,ry)).Normalised();
		this->setCollisionNormal(normal);

		return true;
	}

	return false;
}