#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "Vector2.h";
#include "Paddle.h"
#include "LTimer.h"
#include "Ball.h"
#include <vector>
#include "CollisionVolume.h"
#include "RectangleCollider.h"
#include "CircleCollider.h"
#include "LTexture.h"
#include <random>
using namespace std;

// Starts up SDL and creates a game window
bool init();

// Closes down SDL 
void close();

// Handles game window rendering 
void renderWindow();

// Handles paddle movement
void handleMovement(SDL_Event* e);

// Handles collisions
void handleCollisions();

// Resets ball location
void resetBall();

// Resets game when someone wins 
void resetGame();

// Renders text to window
void renderText(std::string text, Vector2 pos);

// Player victory flag
bool playerHasWon = false;

// Game window constants
const int SCREEN_WIDTH = 858;
const int SCREEN_HEIGHT = 525;
const int SCREEN_FPS = 144;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

// Game object constants
const int PADDLE_HEIGHT = 54;
const int PADDLE_WIDTH = 8;
const int PADDLE_DIST_FROM_EDGE = 100;
const int BALL_RADIUS = 10;

// Game score constants
int p1_score = 0;
int p2_score = 0;
int max_score = 3;

// Essential SDL components
SDL_Window* game_window = NULL;
SDL_Renderer* game_renderer = NULL;
TTF_Font* game_font = NULL;
LTexture game_textTexture;

// Player paddles
Paddle player1(Vector2(PADDLE_DIST_FROM_EDGE, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2), Vector2(PADDLE_WIDTH, PADDLE_HEIGHT), { 255,255,255,0 });
Paddle player2(Vector2(SCREEN_WIDTH - PADDLE_DIST_FROM_EDGE, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2), Vector2(PADDLE_WIDTH, PADDLE_HEIGHT), { 255,255,255,0 });

// Ball
Ball ball(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), BALL_RADIUS, { 255,255,255,0 });

// Game Object colliders
RectangleCollider* player1_col;
RectangleCollider* player2_col;
CircleCollider* ball_col;


int main( int argc, char* args[] ) {

	if ( init() ) 
	{
	
		// Main game loop flag
		bool quit = false;

		// Event handler
		SDL_Event e;

		// FPS timer
		LTimer fpsTimer;

		// FPS cap timer
		LTimer capTimer;

		// Start counting frames
		int countedFrames = 0;
		fpsTimer.start();

		// Get colliders
		player1_col = dynamic_cast<RectangleCollider*>(player1.getCollider());
		player2_col = dynamic_cast<RectangleCollider*>(player2.getCollider());
		ball_col = dynamic_cast<CircleCollider*>(ball.getCollider());
	
		resetBall();
		
		// Game loop
		while ( !quit )
		{
			// Start cap timer
			capTimer.start();

			// While event queue not empty
			while ( SDL_PollEvent(&e) ) {

				// Quit game
				if ( e.type == SDL_QUIT )
				{
					quit = true;
				}
				// If player has won listen for 'r' keypress to reset game
				else if (playerHasWon && e.key.keysym.sym == SDLK_r)
				{
					resetGame();
					playerHasWon = false;
				}
				// Handle user control input
				else
				{
					handleMovement( &e );
				}
			}

			// Skip these steps while rendering victory screen
			// ~ Super lazy way to handle player victory event ~
			if (!playerHasWon)
			{
				handleCollisions();

				// Update game object physics
				player1.updateObject(game_renderer);
				player2.updateObject(game_renderer);
				ball.updateObject(game_renderer);
			}

			renderWindow();

			// Calculate and correct fps
			float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
			if (avgFPS > 200000) { avgFPS = 0; }		

			// If frame finished early
			int frameTicks = capTimer.getTicks();
			if ( frameTicks < SCREEN_TICKS_PER_FRAME )
			{
				// Wait remaining time
				SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
			}

			++countedFrames;
			// Check if someone has reached max score
			if (!playerHasWon)
				if (p1_score == max_score || p2_score == max_score) { playerHasWon = true; }
		} // Game loop
	} // if ( init ) 

	close();

	return 0;
}

bool init()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL video subsystem
	if ( SDL_InitSubSystem( SDL_INIT_VIDEO ) != 0 )
	{
		SDL_Log("Unable to intialize SDL: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create game window
		game_window = SDL_CreateWindow( "Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0 );

		if ( game_window == NULL )
		{
			SDL_Log("Unable to intialize game window: %s\n", SDL_GetError());
			success = false;
		}

		// Create renderer
		game_renderer = SDL_CreateRenderer( game_window, -1, SDL_RENDERER_ACCELERATED );
		
		if (game_renderer == NULL)
		{
			SDL_Log("Unable to intialize game renderer: %s\n", SDL_GetError());
			success = false;
		}

	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("Unable to initialize SDL_image: %s\n", IMG_GetError());
		success = false;
	}

	// Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		SDL_Log("Unable to initialize SDL_ttf: %s\n", TTF_GetError());
		success = false;
	}

	// Open the font
	game_font = TTF_OpenFont("OpenSans-ExtraBold.ttf", 36);
	if (game_font == NULL)
	{
		SDL_Log("Unable to load font: % s\n", TTF_GetError());
		success = false;
	}

	return success;
}

void close()
{
	// Free loaded images
	game_textTexture.free();

	// Free font
	TTF_CloseFont( game_font );
	
	SDL_DestroyWindow( game_window );
	SDL_DestroyRenderer( game_renderer );
	
	game_window = NULL;
	game_renderer = NULL;
	game_font = NULL;

	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
}

void handleMovement( SDL_Event* e ) {
	
	// Key pressed event
	if ( e->type == SDL_KEYDOWN ) 
	{
		switch ( e->key.keysym.sym )
		{
		case SDLK_w:
				player1.setState(Paddle::PaddleState::MoveUp);
			break;
		
		case SDLK_s:
			player1.setState(Paddle::PaddleState::MoveDown);
			break;

		case SDLK_UP:
			player2.setState(Paddle::PaddleState::MoveUp);
			break;

		case SDLK_DOWN:
			player2.setState(Paddle::PaddleState::MoveDown);
			break;
		}
	} 
	// Key released event
	else if (e->type == SDL_KEYUP)
	{
		switch (e->key.keysym.sym) 
		{
		case SDLK_w:
			if(player1.getState() != Paddle::PaddleState::MoveDown) // Prevent release of 'w' key triggering idle if 's' is pressed before 'w' is released
				player1.setState(Paddle::PaddleState::Idle);
			break;

		case SDLK_s:
			if (player1.getState() != Paddle::PaddleState::MoveUp)
			player1.setState(Paddle::PaddleState::Idle);
			break;

		case SDLK_UP:
			if (player2.getState() != Paddle::PaddleState::MoveDown)
				player2.setState(Paddle::PaddleState::Idle);
			break;

		case SDLK_DOWN:
			if (player2.getState() != Paddle::PaddleState::MoveUp)
				player2.setState(Paddle::PaddleState::Idle);
			break;
		}
	}
}


void handleCollisions() {

	// Handle ball collision with map edge

	// Top and Bottom edges
	if (ball.getPosition().y > SCREEN_HEIGHT - ball_col->getRadius() || ball.getPosition().y < ball_col->getRadius())
		ball.inverseDirection_y();

	int goalDistanceTriggerOffset = 150; // Distance to go off-screen before a goal is counted

	// Right edge
	if (ball.getPosition().x > SCREEN_WIDTH + goalDistanceTriggerOffset)
	{
		p1_score++;
		resetBall();
	}

	// Left edge
	if (ball.getPosition().x < 0 - goalDistanceTriggerOffset)
	{
		p2_score++;
		resetBall();
	}

	// Test ball and paddle collisions
	ball_col->isCollision(player1_col, game_renderer);
	ball_col->isCollision(player2_col, game_renderer);
}

void resetBall()
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

	std::uniform_int_distribution<> genNewY(BALL_RADIUS, SCREEN_HEIGHT-BALL_RADIUS);	// Generate new Y position to spawn
	
	std::uniform_real_distribution<> genNewSpeed_y(0, .5);   // Generates speed in y axis
	std::uniform_real_distribution<> genNewSpeed_x(0.2, 1);  // Generates speed in x axis  
	
	std::uniform_int_distribution<> genDirection(-1, 0);	// Generates new direction for x axis: left (-1) or right (0), and y axis: up (-1) or down (0)
	
	// Generate directions for x and y
	int direction_x = genDirection(gen);
	int direction_y = genDirection(gen);

	// Generate new y position
	int new_y = genNewY(gen);
	
	// Calculate new directions
	float new_dir_x = genNewSpeed_x(gen);
	float new_dir_y = genNewSpeed_y(gen);

	if (direction_x < 0)	// If goes left
		new_dir_x *= -1;

	if (direction_y < 0)	// If goes up
		new_dir_y *= -1;

	// Set new position and direction
	ball.setPosition(Vector2(SCREEN_WIDTH / 2, new_y));
	ball.setDirection(Vector2(new_dir_x, new_dir_y));
}

void renderWindow() {
	// Clear window
	SDL_RenderClear( game_renderer );
	
	// Draw black background
	SDL_Rect background = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_SetRenderDrawColor( game_renderer, 0, 0, 0, 0 );
	SDL_RenderFillRect( game_renderer, &background );
	
	// Render score
	int offsetFromCenter = 200;
	int height = 50;
	renderText(std::to_string(p1_score),  Vector2(SCREEN_WIDTH / 2 - offsetFromCenter, height));
	renderText(std::to_string(p2_score),  Vector2(SCREEN_WIDTH / 2 + offsetFromCenter, height));
	
	// Draw middle line
	SDL_SetRenderDrawColor(game_renderer, 255, 255, 255, 0);
	SDL_RenderDrawLine(game_renderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);

	// Draw objects
	player1.drawSelf( game_renderer );
	player2.drawSelf( game_renderer );
	ball.drawSelf( game_renderer );

	// Draw victory screen
	if (playerHasWon)
	{
		// Render winner sign
		if (p1_score == max_score) // Player 1 won
			renderText("Winner", Vector2(SCREEN_WIDTH / 2 - offsetFromCenter, height*2));
		else 
			renderText("Winner", Vector2(SCREEN_WIDTH / 2 + offsetFromCenter, height*2));
		
		// Render reset text
		renderText("Press 'r' to restart", Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	}
	// Render window
	SDL_RenderPresent( game_renderer );
}

void renderText(std::string text, Vector2 pos)
{
		SDL_Color textColor = { 255,255,255,0 };
		
		if (!game_textTexture.loadFromRenderedText(game_renderer, game_font, text, textColor))
		{
			SDL_Log("Unable to render text texture\n");
		}

		game_textTexture.render(game_renderer, pos.x, pos.y);
}

void resetGame() {
	// Reset paddle position
	player1.setPosition(Vector2(PADDLE_DIST_FROM_EDGE, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2));
	player2.setPosition(Vector2(SCREEN_WIDTH - PADDLE_DIST_FROM_EDGE, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2));
	
	resetBall();

	p1_score = 0;
	p2_score = 0;
}