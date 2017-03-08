#pragma once

#include "Tile.h"

class TileGraph
{
public:
	TileGraph();
	TileGraph(int w, int h);
	~TileGraph();

	void Setup(int w, int h);

	Tile* GetTileAt(int x, int y);

private:
	Tile* tiles;
	int width;
	int height;

	int GetIndex(int x, int h);
};

