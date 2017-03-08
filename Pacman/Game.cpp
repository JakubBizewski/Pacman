#include "Game.h"
#include "Pacman.h"

Game* Game::GameInstance = NULL;

Game::Game(std::string name, int screenW, int screenH)
{
	GameInstance = this;

	name = name;

	screenW = screenW;
	screenH = screenH;
}

bool Game::Initialize()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialized! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Create window
	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenW, screenH, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		// Create software renderer if we couldn't create hardware accelerated one.
		// TODO: Works too fast, need a frame cap
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

		if (renderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	//Initialize SDL_ttf module
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialized! TTF Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

bool Game::LoadMedia()
{
	if (!pacman.LoadMedia())
		return false;

	gameObjectList.push_back(&pacman);

	return true;
}

void Game::Close()
{
	for (unsigned int i = 0; i < gameObjectList.size(); i++)
		gameObjectList[i]->Free();

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	TTF_Quit();
}

void Game::Start()
{
	//Start up SDL and create window
	if (!Initialize())
	{
		printf("Failed to initialize!\n");
		return;
	}

	//Load media
	if (!LoadMedia())
	{
		printf("Failed to load media!\n");
		Close();

		return;
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

			for (unsigned int i = 0; i < gameObjectList.size(); i++)
				gameObjectList[i]->HandleEvents(&e);
		}

		for (unsigned int i = 0; i < gameObjectList.size(); i++)
			gameObjectList[i]->Update();

		// Fill the screen with black
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		for (unsigned int i = 0; i < gameObjectList.size(); i++)
			gameObjectList[i]->Render();

		//Update the surface
		SDL_RenderPresent(renderer);
	}

	//Free resources and close SDL
	Close();
}

SDL_Window* Game::GetWindow()
{
	return window;
}

SDL_Renderer* Game::GetRenderer()
{
	return renderer;
}

Game::~Game()
{
	Close();
}
