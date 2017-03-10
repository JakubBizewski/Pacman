#pragma once

#include <SDL.h>

class Pacman;
class Wall;

class Tile
{
public:
	Tile();
	Tile(int x, int y);

	// Sets pointer to Pacman in the tile
	void SetPacman(Pacman* pacman);

	// Sets pointer to wall in the tile
	void SetWall(Wall* wall);

	// Sets position of the tile
	void SetPos(int x, int y);

	// Returns pointer to Pacman in the tile
	Pacman* GetPacman();
	
	// Returns pointer to wall in the tile
	Wall* GetWall();

	// Returns position of the tile
	SDL_Point GetPosition();

private:
	SDL_Point position;
	
	// GameObjects

	Pacman* pPacman;
	Wall* pWall;
};

