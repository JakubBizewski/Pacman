#pragma once

#include <queue>
#include <unordered_map>
#include <functional>

#include "TileGraph.h"
#include "PriorityQueue.h"

class PathFinder
{
public:
	PathFinder(TileGraph* tileGraph);

	// Calculate a path for tile to tile
	std::vector<Tile*> CalculateRoute(Tile* start, Tile* goal);

	// Set a function, which will determine what to avoid
	void SetAvoidFunction(function<bool(Tile*)> newFunction);

private:
	static inline float Heuristic(Tile* a, Tile* b);

	TileGraph* pTileGraph;
	function<bool(Tile*)> avoidFunction;
};

