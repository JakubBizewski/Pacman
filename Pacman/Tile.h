#pragma once

#include <SDL.h>

class Pacman;
class Wall;
class Point;
class Blinky;

class Tile
{
public:
	const static int Width = 25;
	const static int Height = 25;

	Tile();
	Tile(int x, int y);

	// Sets pointer to Pacman in the tile
	void SetPacman(Pacman* pacman);

	// Sets pointer to wall in the tile
	void SetWall(Wall* wall);

	// Sets pointer to point in the tile
	void SetPoint(Point* wall);

	// Sets pointer to Blinky in the tile
	void SetBlinky(Blinky* blinky);

	// Sets position of the tile
	void SetPos(int x, int y);

	// Returns pointer to Pacman in the tile
	Pacman* GetPacman();
	
	// Returns pointer to wall in the tile
	Wall* GetWall();

	// Returns pointer to wall in the tile
	Point* GetPoint();

	// Returns pointer to wall in the tile
	Blinky* GetBlinky();

	// Returns position of the tile
	SDL_Point GetPosition();

private:
	SDL_Point position;
	
	// GameObjects

	Pacman* pPacman;
	Wall* pWall;
	Point* pPoint;
	Blinky* pBlinky;
};

