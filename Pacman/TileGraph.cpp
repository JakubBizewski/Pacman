#include "TileGraph.h"

TileGraph::TileGraph(int w, int h)
{
	tiles = new Tile[w*h];

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
	if (x > width || y > height)
		return -1;

	if (x < 0 || y < 0)
		return -1;

	return x + y * width;
}