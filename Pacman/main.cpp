//Using SDL, standard IO, and strings
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Texture.h"
#include "Pacman.h"
#include "Wall.h"
#include "Point.h"
#include "Misc.h"
#include "TileGraph.h"
#include "MapGenerator.h"
#include "TextureManager.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

TextureManager gTextureManager;

std::vector<GameObject*> gGameObjectList;

TileGraph gTileGraph(20, 20);

MapGenerator gMapGenerator(&gTileGraph, &gTextureManager);

bool init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialized! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Create window
	gWindow = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Create renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL) {
		// Create software renderer if we couldn't create hardware accelerated one.
		// TODO: Works too fast, need a frame cap
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
		
		if (gRenderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: Linear texture filtering not enabled!");
	}

	//Initialize SDL_ttf module
	if (TTF_Init() == -1) {
		printf("SDL_ttf could not initialized! TTF Error: %s\n", TTF_GetError());
		return false;
	}

	Texture::Renderer = gRenderer;

	return true;
}

bool loadMedia()
{
	// Load textures
	Texture* wallTexture = new Texture();
	if (!wallTexture->LoadFromImage("./Resources/wall_sprite.bmp"))
		return false;

	Texture* pointTexture = new Texture();
	if (!pointTexture->LoadFromImage("./Resources/point2.bmp"))
		return false;

	Texture* pacmanTexture = new Texture();
	if (!pacmanTexture->LoadFromImage("./Resources/PacMan.bmp"))
		return false;

	// Set static variables for objects
	// NOTE: Should this be changed?
	GameObject::tileGraph = &gTileGraph;

	// Add loaded textures to a TextureManager
	gTextureManager.Add("wall", wallTexture);
	gTextureManager.Add("point", pointTexture);
	gTextureManager.Add("pacman", pacmanTexture);

	Wall::CreateClips();

	// Load map
	if (!gMapGenerator.Load("./Resources/mapa.txt"))
		return false;

	gMapGenerator.Populate(gGameObjectList);

	return true;
}

void close()
{
	// Free all objects
	for (unsigned int i = 0; i < gGameObjectList.size(); i++)
		delete gGameObjectList[i];

	// Free all textures
	gTextureManager.Free();

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	TTF_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
		return -1;
	}

	//Load media
	if (!loadMedia()) {
		printf("Failed to load media!\n");
		close();

		return -2;
	}

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		// Remove all objects marked for deletion from gameobjects vector
		for (unsigned int i = 0; i < gGameObjectList.size(); i++) {
			if (gGameObjectList[i]->ToDelete()) {
				delete gGameObjectList[i];
				removeFromVector(gGameObjectList, *gGameObjectList[i]);
			}
		}

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			// Handle the event for all the objects
			for (unsigned int i = 0; i < gGameObjectList.size(); i++)
				gGameObjectList[i]->HandleEvents(&e);
		}

		// Update the logic on all objects
		for (unsigned int i = 0; i < gGameObjectList.size(); i++)
			gGameObjectList[i]->Update();

		// Fill the screen with black
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

		// Render all the objects
		for (unsigned int i = 0; i < gGameObjectList.size(); i++)
			gGameObjectList[i]->Render();

		//Update the surface
		SDL_RenderPresent(gRenderer);
	}

	//Free resources and close SDL
	close();

	return 0;
}