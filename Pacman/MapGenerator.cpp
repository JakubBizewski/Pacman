#include "MapGenerator.h"

MapGenerator::MapGenerator(TileGraph* tileGraph, TextureManager* textureManager)
{
	pTileGraph = tileGraph;
	pTextureManager = textureManager;
}

bool MapGenerator::Load(std::string path)
{
	std::fstream file;

	file.open(path.c_str(), std::ios::in);

	if (file.is_open() == false)
		return false;

	std::string line;

	/*
	while (std::getline(file, line))
	{
		printf((line + "\n").c_str());
	}
	*/

	int x = 0;
	int y = 0;

	while (std::getline(file, line)) {
		std::vector<char> chars(line.begin(), line.end());

		for (int x = 0; x < chars.size(); x++) {
			GameObject* newObject = NULL;
			Tile* tile = pTileGraph->GetTileAt(x, y);

			switch (chars[x])
			{
				case 'x':
					newObject = new Wall(tile, pTextureManager->Get("wall"));
					//tile->SetWall((Wall*) newObject);

					break;
				case '.':
					newObject = new Point(tile, pTextureManager->Get("point"));
					//tile->SetPoint((Point*) newObject);

					break;
				case 'p':
					newObject = new Pacman(tile, pTextureManager->Get("pacman"));
					//tile->SetPacman((Pacman*) newObject);

					break;
			}

			objectVector.push_back(newObject);
		}

		y++;
	}

	file.close();

	for (int i = 0; i < objectVector.size(); i++) {
		objectVector[i]->Free();
		delete objectVector[i];
	}

	return true;
}

void MapGenerator::Populate(std::vector<GameObject*>& vector)
{

}
