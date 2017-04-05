#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "Wall.h"
#include "TileGraph.h"
#include "Point.h"
#include "Pacman.h"
#include "TextureManager.h"

class GameObject;

class MapGenerator
{
public:
	MapGenerator(TileGraph* tileGraph, TextureManager* textureManager);

	bool Load(std::string path);

	void Populate(std::vector<GameObject*>& vector);

private:
	std::vector<GameObject*> objectVector;

	TileGraph* pTileGraph;
	TextureManager* pTextureManager;
};

