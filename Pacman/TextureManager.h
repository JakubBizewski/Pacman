#pragma once

#include <unordered_map>

#include "Texture.h"

class TextureManager
{
public:
	// Add a texture to the manager
	void Add(std::string key, Texture* texture);

	// Get a texture based on the key
	Texture* Get(std::string key);

	// Releases all memory related to textures stored
	// by the TextureManager
	void Free();

	~TextureManager();

private:
	std::unordered_map<std::string, Texture*> texturesMap;
};

