#pragma once

#include "Tile.h"

class TileGraph
{
public:
	TileGraph(int w, int h);
	~TileGraph();

	Tile* GetTileAt(int x, int y);

private:
	Tile* tiles;
	int width;
	int height;

	int GetIndex(int x, int h);
};

