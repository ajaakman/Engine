#include <cstddef>

#include "Sprite.h"
#include "Graphics/Renderer/Vertex.h"
#include "Errors.h"

Sprite::Sprite()
	:m_vboID(0)
{	
}

Sprite::~Sprite()
{
	if (m_vboID != 0)
	{
		GL(glDeleteBuffers(1, &m_vboID));
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
		GL(glGenBuffers(1, &m_vboID));
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
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}

	vertexData[1].color.r = 0;
	vertexData[1].color.g = 0;
	vertexData[1].color.b = 255;
	
	vertexData[4].color.r = 0;
	vertexData[4].color.g = 255;
	vertexData[4].color.b = 0;

	GL(glBindBuffer(GL_ARRAY_BUFFER, m_vboID));
	GL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW));

	GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Sprite::Draw()
{
	GL(glBindBuffer(GL_ARRAY_BUFFER, m_vboID));
	GL(glEnableVertexAttribArray(0));

	GL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)));
	GL(glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)));

	GL(glDrawArrays(GL_TRIANGLES, 0, 6));


	GL(glDisableVertexAttribArray(0));
	GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
