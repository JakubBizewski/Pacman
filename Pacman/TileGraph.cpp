#include "TileGraph.h"

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

int TileGraph::GetIndex(int x, int y)
{
	if (x >= width || y >= height)
		return -1;

	if (x < 0 || y < 0)
		return -1;

	return x + y * width;
}