#pragma once

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
// #include <SDL_image.h>

class Texture
{
public:
	// Static SDL_Renderer so we don't have to ask for it
	// when creating the texture or when rendering
	// TODO: Temporary solution, should be removed after implementation of Game class
	static SDL_Renderer* Renderer;

	Texture();
	~Texture();

	// Load texture from file
	bool LoadFromImage(std::string path, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0);

	// Load texture from rendered text
	bool LoadFromRenderedText(TTF_Font* font, std::string text, SDL_Color textColor);

	// Render the texture
	void Render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip renderFlip = SDL_FLIP_NONE);

	// Set color
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);

	// Set blend mode
	void SetBlendMode(SDL_BlendMode blendMode);

	// Set alpha
	void SetAlpha(Uint8 alpha);

	// Free assets
	void Free();

	int GetWidth();
	int GetHeight();

private:
	// Actual texture
	SDL_Texture* texture;

	int width;
	int height;
};

