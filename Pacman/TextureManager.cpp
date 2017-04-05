#include "TextureManager.h"

TextureManager::TextureManager()
{

}

void TextureManager::Add(std::string key, Texture* texture)
{
	texturesMap.insert(std::make_pair(key, texture));
}

Texture* TextureManager::Get(std::string key)
{
	return texturesMap[key];
}

void TextureManager::Free()
{
	for (auto &pair : texturesMap) {
		delete pair.second;
	}
}

TextureManager::~TextureManager()
{
	Free();
}
