#include "ResourceManager.h"

TextureCache ResourceManager::m_TextureCache;

GLTexture ResourceManager::getTexture(std::string texturePath)
{
	return m_TextureCache.getTexture(texturePath);
}
