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

bool Texture::LoadFromImage(std::string path, Uint8 r, Uint8 g, Uint8 b)
{
	// Free the previous texture
	Free();

	// Return if the renderer was not set
	if (Renderer == NULL)
		return false;

	// Load image to a surface
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		return false;
	}

	// Set color key
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, r, g, b));

	// Create texture from the surface
	texture = SDL_CreateTextureFromSurface(Texture::Renderer, loadedSurface);
	if (texture == NULL) {
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

bool Texture::LoadFromRenderedText(TTF_Font* font, std::string text, SDL_Color textColor)
{
	// Free the previous texture
	Free();

	// Return if the renderer was not set
	if (Renderer == NULL)
		return false;

	// Render the text using SDL_ttf library
	SDL_Surface* loadedSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if (loadedSurface == NULL) {
		printf("Unable to render text! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	// Create a texture from generated surface
	texture = SDL_CreateTextureFromSurface(Texture::Renderer, loadedSurface);
	if (texture == NULL) {
		printf("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Set width and height of the texture
	width = loadedSurface->w;
	height = loadedSurface->h;

	// Free the surface
	SDL_FreeSurface(loadedSurface);

	return true;
}

void Texture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip renderFlip)
{
	// Return if the renderer was not set
	if (Renderer == NULL)
		return;

	SDL_Rect renderQuad = { x, y, GetWidth(), GetHeight() };

	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(Renderer, texture, clip, &renderQuad, angle, center, renderFlip);
}

void Texture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(texture, red, green, blue);
}

void Texture::SetBlendMode(SDL_BlendMode blendMode)
{
	SDL_SetTextureBlendMode(texture, blendMode);
}

void Texture::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::Free()
{
	if (texture != NULL) {
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