#include "Tile.h"

Tile::Tile()
{
	position = { 0,0 };

	pPacman = NULL;
	pWall = NULL;
	pPoint = NULL;
}

Tile::Tile(int x, int y)
{
	position = { x,y };

	pPacman = NULL;
	pWall = NULL;
	pPoint = NULL;
}

void Tile::SetPos(int x, int y)
{
	position.x = x;
	position.y = y;
}

void Tile::SetPacman(Pacman* pacman)
{
	pPacman = pacman;
}

void Tile::SetWall(Wall* wall)
{
	pWall = wall;
}

void Tile::SetPoint(Point* point)
{
	pPoint = point;
}

void Tile::SetBlinky(Blinky* blinky)
{
	pBlinky = blinky;
}

Pacman* Tile::GetPacman()
{
	return pPacman;
}

Wall* Tile::GetWall()
{
	return pWall;
}

Point* Tile::GetPoint()
{
	return pPoint;
}

Blinky* Tile::GetBlinky()
{
	return pBlinky;
}

SDL_Point Tile::GetPosition()
{
	return position;
}