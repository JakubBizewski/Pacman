#pragma once

#include <unordered_map>

#include "Texture.h"

class TextureManager
{
public:
	TextureManager();

	void Add(std::string key, Texture* texture);
	Texture* Get(std::string key);

	void Free();

	~TextureManager();

private:
	std::unordered_map<std::string, Texture*> texturesMap;
};

