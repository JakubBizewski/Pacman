#pragma once

#include "GameObject.h"
#include "Texture.h"
#include "TileGraph.h"

class Point : public GameObject
{
public:
	//static TileGraph* tileGraph;

	// Prefixed width and height of a wall
	static const int Width = 3;
	static const int Height = 3;

	static const int Margin = 11;

	// Point();

	Point(Tile* tile, Texture* texture);
	~Point();

	// Loads texture and sets up animation clips
	// bool LoadMedia();

	// Sets the tile of the wall
	void SetTile(Tile* newTile);

	// Renders pacman
	void Render();

	// Releases texture memory
	// void Free();

	// Mark the object to be deleted
	void Delete();

	// Returns collider
	SDL_Rect GetCollider();

	// Returns position
	SDL_Point GetPosition();

	// Returns wall's tile
	Tile* GetTile();

private:
	Texture* pointTexture;

	SDL_Point position;

	Tile* currTile;

	SDL_Rect collider;
};

