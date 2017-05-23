#include "PathFinder.h"

PathFinder::PathFinder(TileGraph* tileGraph)
{
	pTileGraph = tileGraph;
}

std::vector<Tile*>* PathFinder::CalculateRoute(Tile* start, Tile* goal)
{
	std::unordered_map<Tile*, Tile*> came_from;
	std::unordered_map<Tile*, float> cost_so_far;

	PriorityQueue<Tile*, float> frontier;

	came_from[start] = start;
	cost_so_far[start] = 0;

	frontier.put(start, 0);

	while (!frontier.empty())
	{
		Tile* current = frontier.get();

		if (current == goal)
			break;

		for (auto next : pTileGraph->GetNeighbours(current)) {
			float new_cost = cost_so_far[current] + 1;

			if (next != NULL && (!cost_so_far.count(next) || new_cost < cost_so_far[next]) && next->GetWall() == NULL)
			{
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

	while (current != start)
	{
		current = came_from[current];
		path.push_back(current);
	}

	reverse(path.begin(), path.end());

	return &path;
}

inline float PathFinder::Heuristic(Tile* a, Tile* b)
{
	return std::abs(a->GetPosition().x - b->GetPosition().x) + std::abs(a->GetPosition().y - b->GetPosition().y);
}
