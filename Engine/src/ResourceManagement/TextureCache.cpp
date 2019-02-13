#include "TextureCache.h"
#include "Utililites/ImageLoader.h"
#include <iostream>

Engine::TextureCache::TextureCache()
{
}


Engine::TextureCache::~TextureCache()
{
}

Engine::GLTexture Engine::TextureCache::getTexture(std::string texturePath)
{
	auto mit = m_TextureMap.find(texturePath);

	if (mit == m_TextureMap.end())
	{
		GLTexture newTexture = ImageLoader::loadPNG(texturePath);

		m_TextureMap.insert(std::make_pair(texturePath, newTexture));
		
		//std::cout << "Loaded Texture!\n";
		return newTexture;
	}
	//std::cout << "Used Cached Texture!\n";

	return mit->second;
}
