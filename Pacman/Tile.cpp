#include "Tile.h"

Tile::Tile()
{
	position = { 0,0 };
	pPacman = NULL;
	pWall = NULL;
}

Tile::Tile(int x, int y)
{
	position = { x,y };
	pPacman = NULL;
	pWall = NULL;
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

Pacman* Tile::GetPacman()
{
	return pPacman;
}

Wall* Tile::GetWall()
{
	return pWall;
}

SDL_Point Tile::GetPosition()
{
	return position;
}