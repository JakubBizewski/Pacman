#pragma once

#include<string>
#include<SDL.h>
//#include<SDL_image.h>

class Texture
{
public:
	// Static SDL_Renderer so we don't have to ask for it
	// when creating the texture or when rendering
	static SDL_Renderer* Renderer;

	Texture();
	~Texture();

	// Load texture from file
	bool Load(std::string path);

	// Render the texture
	void Render(int x, int y, SDL_Rect* clip = NULL);

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

