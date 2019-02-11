#include "ImageLoader.h"
#include "Utililites/picoPNG.h"
#include "Utililites/IOManager.h"
#include "Utililites/Errors.h"

GLTexture ImageLoader::loadPNG(std::string filePath)
{
	GLTexture texture = {};

	std::vector<unsigned char> in;
	std::vector<unsigned char> out;

	unsigned long width, height;

	if (IOManager::readFileToBuffer(filePath, in) == false)
		FatalError("Failed to load PNG file To buffer");

	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
	if (errorCode != 0)	
		FatalError("picoPNG decodePNG() failed with error: " + std::to_string(errorCode));
	
	GL(glGenTextures(1, &(texture.id)));

	GL(glBindTexture(GL_TEXTURE_2D, texture.id));

	GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0])));

	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));

	GL(glGenerateMipmap(GL_TEXTURE_2D));

	GL(glBindTexture(GL_TEXTURE_2D, 0));

	texture.width = width;
	texture.height = height;

	return texture;
}
