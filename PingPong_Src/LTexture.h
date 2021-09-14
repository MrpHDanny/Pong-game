#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
class LTexture
{
public:

	LTexture();
	~LTexture();

	// Loads image at specified path
	bool loadFromFile(SDL_Renderer* game_renderer, std::string path);
	
	//Creates image from font string
	bool loadFromRenderedText(SDL_Renderer* rend, TTF_Font* game_font, std::string textureText, SDL_Color textColor);

	// Deallocates texture
	void free();

	// Renders texture at given point
	void render(SDL_Renderer* game_renderer, int x, int y, SDL_Rect* clip = NULL);

	// Gets image dimension
	int getWidth() const { return mWidth; };
	int getHeight() const { return mHeight; };

private:
	SDL_Texture* mTexture;

	// Image dimensions
	int mWidth;
	int mHeight;
};

