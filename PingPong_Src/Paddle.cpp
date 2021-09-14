#include "Paddle.h"
#include "RectangleCollider.h"
#include <iostream>

using namespace std;

Paddle::Paddle( Vector2 pos, Vector2 size, SDL_Color color ) : GameObject() 
{
	setPosition(pos);
	currentState = PaddleState::Idle;
	this->size = size;
	renderBody = { (int)pos.x, (int)pos.y, (int)size.x, (int)size.y };
	renderBodyColor = color;
	setCollider(new RectangleCollider(size.x, size.y, pos, this));
}

void Paddle::updateObject(SDL_Renderer* game_renderer) 
{

	// Get game window height
	int window_h;
	SDL_GetRendererOutputSize(game_renderer, NULL , &window_h);
	
	// Restring movement outside of game window
	if ( getState() == Paddle::PaddleState::MoveUp && position.y >= 0)
	{
		setPosition(Vector2(position.x, position.y - speed));
	}
	else if (getState() == Paddle::PaddleState::MoveDown && position.y <= window_h - size.y)
	{
		setPosition(Vector2(position.x, position.y + speed));
	}

	// Update object position
	renderBody = { (int)position.x, (int)position.y, (int)size.x, (int)size.y };

	// Update collider
	collider->setPosition(position);
}

void Paddle::drawSelf(SDL_Renderer* game_renderer)
{
	SDL_SetRenderDrawColor(game_renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(game_renderer, &renderBody);
}