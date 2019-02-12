#include <cstddef>

#include "Sprite.h"
#include "Graphics/Renderer/Vertex.h"
#include "Utililites/Errors.h"
#include "ResourceManagement/ResourceManager.h"

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

void Sprite::Init(float x, float y, float width, float height, std::string texutePath)
{
	m_nX = x;
	m_nY = y;
	m_nWidth = width;
	m_nHeight = height;
	m_Texture = ResourceManager::getTexture(texutePath);

	if (m_vboID == 0)
	{
		GL(glGenBuffers(1, &m_vboID));
	}

	Vertex vertexData[6];
	// First triangle.
	vertexData[0].SetPosition(x + width, y + height);
	vertexData[0].SetUV(1.0f, 1.0f);
	vertexData[1].SetPosition(x, y + height);
	vertexData[1].SetUV(0.0f, 1.0f);
	vertexData[2].SetPosition(x, y);
	vertexData[2].SetUV(0.0f, 0.0f);
	// Second triangle.
	vertexData[3].SetPosition(x, y);
	vertexData[3].SetUV(0.0f, 0.0f);
	vertexData[4].SetPosition(x + width, y);
	vertexData[4].SetUV(1.0f, 0.0f);
	vertexData[5].SetPosition(x + width, y + height);
	vertexData[5].SetUV(1.0f, 1.0f);

	for (int i = 0; i < 6; ++i)			
		vertexData[i].SetColor(255, 0, 255, 255);
		
	vertexData[1].SetColor(0, 0, 255, 255);
	vertexData[4].SetColor(0, 255, 0, 255);

	GL(glBindBuffer(GL_ARRAY_BUFFER, m_vboID));
	GL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW));

	GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Sprite::Draw()
{
	GL(glBindTexture(GL_TEXTURE_2D, m_Texture.id));

	GL(glBindBuffer(GL_ARRAY_BUFFER, m_vboID));
	GL(glEnableVertexAttribArray(0));

	GL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)));
	GL(glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)));
	GL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv)));


	GL(glDrawArrays(GL_TRIANGLES, 0, 6));


	GL(glDisableVertexAttribArray(0));
	GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
