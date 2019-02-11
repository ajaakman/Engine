#pragma once
#include "Graphics/GLTexture.h"

#include <string>

class ImageLoader
{
public:
	static GLTexture loadPNG(std::string filePath);
};

