#pragma once

#include <SDL.h>

class Pacman;

class Tile
{
public:
	Tile();

	// Sets pointer to Pacman in the tile
	void SetPacman(Pacman* pacman);

	// Returns pointer to Pacman in the tile
	Pacman* GetPacman();

	// Returns position of the tile
	SDL_Point GetPosition();

private:
	SDL_Point position;
	
	// GameObjects

	Pacman* pPacman;
};

