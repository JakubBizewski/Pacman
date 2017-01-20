#include "Texture.h"

SDL_Renderer* Texture::Renderer = NULL;

Texture::Texture()
{
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	Free();
}

bool Texture::Load(std::string path)
{
	// Return if the renderer was not set
	if (Renderer == NULL)
		return false;

	// Load image to a surface
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		return false;
	}

	// Create texture from the surface
	texture = SDL_CreateTextureFromSurface(Texture::Renderer, loadedSurface);
	if (texture == NULL)
	{
		printf("Unable to create texture from surface %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		return false;
	}

	// Set width and height of the texture
	width = loadedSurface->w;
	height = loadedSurface->h;

	// Free the surface
	SDL_FreeSurface(loadedSurface);

	return true;
}

void Texture::Render(int x, int y, SDL_Rect* clip)
{
	// Return if the renderer was not set
	if (Renderer == NULL)
		return;

	SDL_Rect renderQuad = { x, y, GetWidth(), GetHeight() };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(Renderer, texture, clip, &renderQuad);
}

void Texture::Free()
{
	if (texture != NULL)
	{
		// Free the texture and set its pointer to NULL
		SDL_DestroyTexture(texture);
		texture = NULL;

		width = 0;
		height = 0;
	}
}

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}