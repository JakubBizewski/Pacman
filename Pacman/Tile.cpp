#include "Tile.h"

Tile::Tile()
{
	position = { 0,0 };
	pPacman = NULL;
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

Pacman* Tile::GetPacman()
{
	return pPacman;
}

SDL_Point Tile::GetPosition()
{
	return position;
}