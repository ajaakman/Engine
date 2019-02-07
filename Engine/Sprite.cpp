#include "Sprite.h"


Sprite::Sprite()
	:m_vboID(0)
{	
}

Sprite::~Sprite()
{
	if (m_vboID != 0)
	{
		glDeleteBuffers(1, &m_vboID);
	}
}

void Sprite::Init(float x, float y, float width, float height)
{
	m_nX = x;
	m_nY = y;
	m_nWidth = width;
	m_nHeight = height;

	if (m_vboID == 0)
	{
		glGenBuffers(1, &m_vboID);
	}

	float vertexData[12];
	// First triangle.
	vertexData[0] = x + width;
	vertexData[1] = y + height;

	vertexData[2] = x;
	vertexData[3] = y + height;

	vertexData[4] = x;
	vertexData[5] = y;
	// Second triangle.
	vertexData[6] = x;
	vertexData[7] = y;

	vertexData[8] = x + height;
	vertexData[9] = y;

	vertexData[10] = x + width;
	vertexData[11] = y + height;

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);


	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
