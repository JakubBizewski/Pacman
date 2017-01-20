//Using SDL, standard IO, and strings
#include <SDL.h>
#include <stdio.h>
#include <string>

#include "Texture.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

SDL_Renderer* gRenderer = NULL;

// Textures
Texture logo;

bool init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Create window
	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Create renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL)
	{
		// Create software renderer if we couldn't create hardware accelerated one.
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
		
		if (gRenderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}
	}

	Texture::Renderer = gRenderer;

	//Get window surface
	gScreenSurface = SDL_GetWindowSurface(gWindow);

	return true;
}

bool loadMedia()
{
	if (!logo.Load("./Resources/logo.bmp"))
		return false;

	return true;
}

void close()
{
	logo.Free();

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
		return -1;
	}

	//Load media
	if (!loadMedia())
	{
		printf("Failed to load media!\n");
		return -1;
	}

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		logo.Render(0, 0);

		//Update the surface
		SDL_RenderPresent(gRenderer);
	}

	//Free resources and close SDL
	close();

	return 0;
}