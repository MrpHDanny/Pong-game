#pragma once
#include "GameObject.h"

class Paddle : public GameObject
{
public:

	Paddle(Vector2 pos, Vector2 size, SDL_Color color);

	void updateObject(SDL_Renderer* game_renderer) override;
	void drawSelf(SDL_Renderer* renderer) override;
	
	enum class PaddleState {
		MoveUp,
		MoveDown,
		Idle
	};
	
	void setState(const PaddleState& newState) { currentState = newState; }
	PaddleState getState() const { return currentState; }

protected:

	Vector2 size;
	PaddleState currentState;
	SDL_Rect renderBody;
	SDL_Color renderBodyColor;
	int speed = 2;
};

