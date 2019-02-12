#pragma once
#include <GL/glew.h>
#include "Graphics/GLTexture.h"
#include <string>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init(float x, float y, float width, float height, std::string texutePath);

	void Draw();

private:
	float m_nX;
	float m_nY;
	float m_nWidth;
	float m_nHeight;
	GLuint m_vboID;

	GLTexture m_Texture;

};

