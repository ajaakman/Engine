#include "ResourceManager.h"

Engine::TextureCache Engine::ResourceManager::m_TextureCache;

Engine::GLTexture Engine::ResourceManager::getTexture(std::string texturePath)
{
	return m_TextureCache.getTexture(texturePath);
}
