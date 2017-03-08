#pragma once

#include <string>
#include <SDL.h>
#include <vector>
#include <algorithm>

#include <SDL.h>
#include <SDL_ttf.h>
#include "Texture.h"
#include "Pacman.h"
#include "Misc.h"
#include "TileGraph.h"
#include "Tile.h"

class Game
{
public:
	static Game* GameInstance;

	Game(std::string name, int screenW, int screenH);
	~Game();

	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();

	void Start();

private:
	bool Initialize();
	bool LoadMedia();
	void Close();

	std::string name;

	int screenW;
	int screenH;

	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<GameObject*> gameObjectList;
	Pacman pacman;
	TileGraph gTileGraph;
};

