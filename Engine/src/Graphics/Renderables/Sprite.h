#pragma once
#include <GL/glew.h>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init(float x, float y, float width, float height);

	void Draw();

private:
	float m_nX;
	float m_nY;
	float m_nWidth;
	float m_nHeight;
	GLuint m_vboID;
};

