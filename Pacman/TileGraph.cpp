#include "TileGraph.h"
#include <algorithm>

TileGraph::TileGraph()
{
	tiles = NULL;

	width = 0;
	height = 0;
}

TileGraph::TileGraph(int w, int h)
{
	// Create a dynamic array of Tiles
	tiles = new Tile[w*h];

	// Set position of all tiles
	// NOTE: This could propably be also made with constructor
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			tiles[x + (y*w)].SetPos(x, y);
		}
	}

	width = w;
	height = h;
}

void TileGraph::Setup(int w, int h)
{
	// If the TileGraph is not empty, empty it
	if (tiles != NULL)
		delete[] tiles;

	tiles = new Tile[w*h];

	// Set position of all tiles
	// NOTE: This could propably be also made with constructor
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			tiles[x + (y*w)].SetPos(x, y);
		}
	}

	width = w;
	height = h;
}

TileGraph::~TileGraph()
{
	delete[] tiles;
}

Tile* TileGraph::GetTileAt(int x, int y)
{
	int index = GetIndex(x, y);
	if (index < 0)
		return NULL;

	return &tiles[index];
}

std::array<Tile*, 4> TileGraph::GetNeighbours(Tile* tile)
{
	std::array<Tile*, 4> neighbours;

	int x = tile->GetPosition().x;
	int y = tile->GetPosition().y;

	neighbours[0] = GetTileAt(x, y + 1);		// N
	neighbours[1] = GetTileAt(x + 1, y);		// E
	neighbours[2] = GetTileAt(x, y - 1);		// S
	neighbours[3] = GetTileAt(x - 1, y);		// W

	return neighbours;
}

std::array<class Tile*, 8> TileGraph::GetNeighboursDiag(class Tile* tile)
{
	std::array<Tile*, 8> neighbours;

	int x = tile->GetPosition().x;
	int y = tile->GetPosition().y;

	neighbours[0] = GetTileAt(x, y + 1);		// N
	neighbours[1] = GetTileAt(x + 1, y);		// E
	neighbours[2] = GetTileAt(x, y - 1);		// S
	neighbours[3] = GetTileAt(x - 1, y);		// W
	neighbours[4] = GetTileAt(x + 1, y + 1);	// NE
	neighbours[5] = GetTileAt(x - 1, y + 1);	// SE
	neighbours[6] = GetTileAt(x - 1, y - 1);	// SW
	neighbours[7] = GetTileAt(x + 1, y - 1);	// NW

	return neighbours;
}

Pacman* TileGraph::GetPacman()
{
	for (unsigned int i = 0; i < width * height; i++) {
		Tile tile = tiles[i];

		if (tile.GetPacman() != NULL)
			return tile.GetPacman();
	}

	return NULL;
}

int TileGraph::GetIndex(int x, int y)
{
	if (x >= width || y >= height)
		return -1;

	if (x < 0 || y < 0)
		return -1;

	return x + y * width;
}