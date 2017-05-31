#include "PathFinder.h"

PathFinder::PathFinder(TileGraph* tileGraph)
{
	pTileGraph = tileGraph;

	// The default avoid function always return false, so we don't avoid anything
	avoidFunction = [](Tile* tile) {
		return false;
	};
}

std::vector<Tile*> PathFinder::CalculateRoute(Tile* start, Tile* goal)
{
	std::unordered_map<Tile*, Tile*> came_from;		// Chosen path
	std::unordered_map<Tile*, float> cost_so_far;	// Cost of movement

	PriorityQueue<Tile*, float> frontier;			// Queue of tiles to check

	came_from[start] = start;
	cost_so_far[start] = 0;

	frontier.put(start, 0);

	while (!frontier.empty())
	{
		// Get a tile with the biggest priority
		Tile* current = frontier.get();

		// If it's the goal, our path is complete
		if (current == goal)
			break;

		// Check all neighbours
		for (auto next : pTileGraph->GetNeighbours(current)) {
			float new_cost = cost_so_far[current] + 1;

			if (next != NULL && (!cost_so_far.count(next) || new_cost < cost_so_far[next]))
			{
				// If there's a wall in the tile, set cost of movement to INFINITY
				// TODO: We shouldn't include those tiles at all!
				if (avoidFunction(next)) new_cost = INFINITY;

				cost_so_far[next] = new_cost;
				float priority = new_cost + Heuristic(next, goal);
				frontier.put(next, priority);
				came_from[next] = current;
			}
		}
	}

	vector<Tile*> path;
	Tile* current = goal;

	path.push_back(current);

	// Add all tiles of the path to a list
	while (current != start)
	{
		current = came_from[current];
		path.push_back(current);
	}

	// Reverse the list, so that we start at the beginning
	reverse(path.begin(), path.end());

	return path;
}

void PathFinder::SetAvoidFunction(function<bool(Tile*)> newFunction)
{
	avoidFunction = newFunction;
}

inline float PathFinder::Heuristic(Tile* a, Tile* b)
{
	return std::abs(a->GetPosition().x - b->GetPosition().x) + std::abs(a->GetPosition().y - b->GetPosition().y);
}
