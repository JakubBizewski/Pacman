#include "Tile.h"

Tile::Tile()
{
	position = { 0,0 };
	pPacman = NULL;
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