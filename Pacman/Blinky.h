#pragma once

#include <algorithm>

#include <SDL.h>
#include "Texture.h"
#include "GameObject.h"
#include "Tile.h"
#include "TileGraph.h"
#include "Point.h"
#include "MoveDirection.h"
#include "PathFinder.h"

class Blinky : public GameObject
{
public:
	// Prefixed width and height of Pacman
	static const int Width = 25;
	static const int Height = 25;

	// Movement per frame
	static const int Velocity = 3;

	Blinky(Tile* tile, Texture* texture);
	~Blinky();

	// Sets the tile of the pacman
	void SetTile(Tile* newTile);

	// Sets the next tile (to which pacman will go)
	void SetNextTile(Tile* newNextTile);

	// Updates the posititon and check collision
	void Update();

	// Renders pacman
	void Render();

	// Mark the object to be deleted
	void Delete();

	// Returns current direction of movement
	MoveDirection GetMoveDirection();

	// Returns collider
	SDL_Rect GetCollider();

	// Returns position
	SDL_Point GetPosition();

	// Returns pacman's tile
	Tile* GetTile();

	// Returns the tile which pacman is going to
	Tile* GetNextTile();

	// Returns true if pacman is moving
	bool IsMoving();

private:
	// Check if pacman is colliding with other collider
	bool CheckForCollision(const SDL_Rect &otherCollider);

	// Check if given collider is colliding with another collider
	bool CheckForCollision(const SDL_Rect &collider, const SDL_Rect &otherCollider);

	Texture* blinkyTexture;

	MoveDirection moveDir;
	MoveDirection nextDir;
	bool moving;

	SDL_Point position;

	Tile* currTile;
	Tile* nextTile;

	std::vector<Tile*> path;

	SDL_Rect collider;
};

