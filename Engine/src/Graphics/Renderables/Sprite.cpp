#include <cstddef>

#include "Sprite.h"
#include "Graphics/Renderer/Vertex.h"

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

	Vertex vertexData[6];
	// First triangle.
	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;

	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;
	// Second triangle.
	vertexData[3].position.x = x;
	vertexData[3].position.y = y;

	vertexData[4].position.x = x + height;
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;

	for (int i = 0; i < 6; ++i)
	{
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 125;
		vertexData[i].color.a = 255;
	}

	vertexData[1].color.r = 125;
	vertexData[1].color.g = 0;
	vertexData[1].color.b = 255;
	
	vertexData[2].color.r = 0;
	vertexData[2].color.g = 152;
	vertexData[2].color.b = 255;

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glDrawArrays(GL_TRIANGLES, 0, 6);


	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
