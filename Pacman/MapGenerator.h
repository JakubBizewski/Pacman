#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "TileGraph.h"
#include "TextureManager.h"

#include "Wall.h"
#include "Point.h"
#include "Pacman.h"
#include "Blinky.h"

class GameObject;

class MapGenerator
{
public:
	MapGenerator(TileGraph* tileGraph, TextureManager* textureManager);

	// Load map file and generate all objects
	bool Load(std::string path);

	// Populate a GameObject* vector with all the generated objects
	void Populate(std::vector<GameObject*>& vector);

private:
	std::vector<GameObject*> objectVector;

	TileGraph* pTileGraph;
	TextureManager* pTextureManager;
};

