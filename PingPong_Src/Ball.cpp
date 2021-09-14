#include "Ball.h"
#include "CircleCollider.h"
#include <iostream>
using namespace std;

Ball::Ball(Vector2 pos, int r, SDL_Color color)
{
	setPosition(pos);
	radius = r;
	renderBodyColor = color;
	setCollider(new CircleCollider(r, pos , this));
}

void Ball::updateObject(SDL_Renderer* game_renderer)
{
	// Set new y axis direction
	if (collider->getCollisionNormal().y != 99)
	{
		direction.y = collider->getCollisionNormal().y;
		position.y += velocity.y;	// Prevents the ball from being stuck in the top/bottom edge of the paddle
	}

	// Set new x axis direction
	if (collider->getCollisionNormal().x != 99)
	{
		direction.x *= -1;		// Ball must bounce in the opposite direction at the same angle it hit the paddle's center
	}

	// Get velocity
	direction.Normalise();			
	velocity = direction * speed;

	// Update object position
	position += velocity;
	
	// Update collider and reset normal
	collider->setPosition(position);
	collider->setCollisionNormal(Vector2(99, 99));
}

void Ball::drawSelf(SDL_Renderer* game_renderer) {
	SDL_SetRenderDrawColor(game_renderer, 255, 255, 255, 0);

	// Mid-Point Circle Drawing Algorithm
	int x = radius, y = 0;
	int x_center = position.x, y_center = position.y;
	int P = 1 - radius;

	while (x > y) 
	{

		if (P <= 0)
			P = P + 2 * y + 1;
		else
		{
			x--;
			P = P + 2 * y - 2 * x + 1;
		}

		if (x < y)
			break;

		/* NOTE
		*
		* This draws a circle by drawing horizontal lines on the calculated circle points.
		* However, this could to be optimized as it draws multiple lines over each other
		* whenever several circle points are on the same y axis.
		*/

		//SDL_RenderDrawPoint(game_renderer, x + x_center, y + y_center);
		//SDL_RenderDrawPoint(game_renderer, -x + x_center, y + y_center);

		SDL_RenderDrawLine(game_renderer, x + x_center, y + y_center, -x + x_center, y + y_center);

		//SDL_RenderDrawPoint(game_renderer, x + x_center, -y + y_center);
		//SDL_RenderDrawPoint(game_renderer, -x + x_center, -y + y_center);

		SDL_RenderDrawLine(game_renderer, x + x_center, -y + y_center, -x + x_center, -y + y_center);


		//SDL_RenderDrawPoint(game_renderer, y + x_center, x + y_center);
		//SDL_RenderDrawPoint(game_renderer, -y + x_center, x + y_center);

		SDL_RenderDrawLine(game_renderer, y + x_center, x + y_center, -y + x_center, x + y_center);

		//SDL_RenderDrawPoint(game_renderer, y + x_center, -x + y_center);
		//SDL_RenderDrawPoint(game_renderer, -y + x_center, -x + y_center);

		SDL_RenderDrawLine(game_renderer, y + x_center, -x + y_center, -y + x_center, -x + y_center);

		y++;
	}
}

void Ball::inverseDirection_y()
{
	setDirection( Vector2( direction.x, direction.y * -1 ));
}

void Ball::inverseDirection_x()
{
	setDirection( Vector2( direction.x * -1, direction.y ));
} 

