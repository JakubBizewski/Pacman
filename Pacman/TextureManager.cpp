#include "TextureManager.h"

void TextureManager::Add(std::string key, Texture* texture)
{
	texturesMap[key] = texture;
}

Texture* TextureManager::Get(std::string key)
{
	return texturesMap[key];
}

void TextureManager::Free()
{
	for (auto &pair : texturesMap) {
		delete pair.second;
		texturesMap.erase(pair.first);
	}
}

TextureManager::~TextureManager()
{
	Free();
}
