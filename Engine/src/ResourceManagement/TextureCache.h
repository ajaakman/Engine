#pragma once
#include <unordered_map>
#include "Graphics/GLTexture.h"

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	GLTexture getTexture(std::string texturePath);

private:
	std::unordered_map<std::string, GLTexture> m_TextureMap;
};

