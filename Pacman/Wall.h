#pragma once

#include "GameObject.h"
#include "Texture.h"
#include "TileGraph.h"

class Wall : public GameObject
{
public:
	static TileGraph* tileGraph;

	// Prefixed width and height of a wall
	static const int Width = 25;
	static const int Height = 25;

	Wall();
	Wall(Tile* tile);
	~Wall();

	// Loads texture and sets up animation clips
	bool LoadMedia();

	// Sets the tile of the wall
	void SetTile(Tile* newTile);

	// Handles key presses
	//void HandleEvents(SDL_Event* event);

	// Updates the posititon and check collision
	//void Update();

	// Renders pacman
	void Render();

	// Releases texture memory
	void Free();

	// Returns collider
	SDL_Rect GetCollider();

	// Returns position
	SDL_Point GetPosition();

	// Returns wall's tile
	Tile* GetTile();

private:
	Texture wallTexture;

	SDL_Point position;

	Tile* currTile;

	SDL_Rect collider;
};

