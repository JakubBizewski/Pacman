#include "MapGenerator.h"

MapGenerator::MapGenerator(TileGraph* tileGraph, TextureManager* textureManager)
{
	pTileGraph = tileGraph;
	pTextureManager = textureManager;
}

bool MapGenerator::Load(std::string path)
{
	std::fstream file;

	// Open the file and check if successful
	file.open(path.c_str(), std::ios::in);

	if (file.is_open() == false)
		return false;

	std::string line;

	int x = 0;
	int y = 0;

	// Read the file line by line
	while (std::getline(file, line)) {
		// Break the line into chars vector
		std::vector<char> chars(line.begin(), line.end());

		for (unsigned int x = 0; x < chars.size(); x++) {
			// If char is blank space, go to the next char
			if (chars[x] == ' ')
				continue;

			GameObject* newObject = NULL;
			Tile* tile = pTileGraph->GetTileAt(x, y);

			// Create diffrent object depending on the char
			switch (chars[x])
			{
				case 'x':
					newObject = new Wall(tile, pTextureManager->Get("wall"));
					tile->SetWall((Wall*) newObject);

					break;
				case '.':
					newObject = new Point(tile, pTextureManager->Get("point"));
					tile->SetPoint((Point*) newObject);

					break;
				case 'p':
					newObject = new Pacman(tile, pTextureManager->Get("pacman"));
					tile->SetPacman((Pacman*) newObject);

					break;
			}

			objectVector.push_back(newObject);
		}

		y++;
	}

	// Close the file
	file.close();

	return true;
}

void MapGenerator::Populate(std::vector<GameObject*>& vector)
{
	for (unsigned int i = 0; i < objectVector.size(); i++) {
		vector.push_back(objectVector[i]);
	}
}
