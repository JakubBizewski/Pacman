#pragma once

#include <queue>
#include <unordered_map>

#include "TileGraph.h"
#include "PriorityQueue.h"

class PathFinder
{
public:
	PathFinder(TileGraph* tileGraph);

	std::vector<Tile*>* CalculateRoute(Tile* start, Tile* goal);

private:
	static inline float Heuristic(Tile* a, Tile* b);

	TileGraph* pTileGraph;
};

