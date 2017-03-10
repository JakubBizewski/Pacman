#pragma once

#include "Tile.h"

class TileGraph
{
public:
	TileGraph();
	TileGraph(int w, int h);
	~TileGraph();

	// (Re)Creates all tiles
	void Setup(int w, int h);

	// Returns tile at given position
	Tile* GetTileAt(int x, int y);

private:
	Tile* tiles;
	int width;
	int height;

	int GetIndex(int x, int h);
};

