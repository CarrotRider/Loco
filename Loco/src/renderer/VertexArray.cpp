#include "stdafx.h"
#include "VertexArray.h"

#include "glad/glad.h"

namespace Loco {

	VertexArray::VertexArray(const Mesh::Vertex* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices, BufferLayout layout)
		: m_NumVerts(numVerts)
		, m_NumIndices(numIndices)
		, m_ID(0), m_ID_VBO(0), m_ID_EBO(0)
	{
		glGenVertexArrays(1, &m_ID);
		glBindVertexArray(m_ID);

		unsigned int vertexSize = GetVertexSize(layout);

		glGenBuffers(1, &m_ID_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID_VBO);
		glBufferData(GL_ARRAY_BUFFER,
			numVerts * vertexSize * sizeof(float), verts, GL_STATIC_DRAW);

		glGenBuffers(1, &m_ID_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		//Layout 临时
		switch (layout)
		{
		case BufferLayout::POS:
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			break;
		case BufferLayout::POS_NORMAL:
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			break;
		case BufferLayout::POS_NORMAL_TEX:
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);
			break;
		case BufferLayout::POS_TEX:
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			break;
		default:
			break;
		}
	}

	VertexArray::VertexArray(const float* verts, unsigned int numVerts, 
		const unsigned int* indices, unsigned int numIndices,
		BufferLayout layout)
		: m_NumVerts(numVerts)
		, m_NumIndices(numIndices)
		, m_ID(0), m_ID_VBO(0), m_ID_EBO(0)
	{
		glGenVertexArrays(1, &m_ID);
		glBindVertexArray(m_ID);
		
		unsigned int vertexSize = GetVertexSize(layout);

		glGenBuffers(1, &m_ID_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID_VBO);
		glBufferData(GL_ARRAY_BUFFER, 
			numVerts * vertexSize * sizeof(float), verts, GL_STATIC_DRAW);

		glGenBuffers(1, &m_ID_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		//Layout 临时
		switch (layout) 
		{
		case BufferLayout::POS:
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			break;
		case BufferLayout::POS_NORMAL:
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			break;
		case BufferLayout::POS_NORMAL_TEX:
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);
			break;
		case BufferLayout::POS_TEX:
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			break;
		default:
			break;
		}
	}

	VertexArray::~VertexArray()
	{
		glDeleteBuffers(1, &m_ID_VBO);
		glDeleteBuffers(1, &m_ID_EBO);
		glDeleteVertexArrays(1, &m_ID);
	}

	void VertexArray::SetActive(bool active)
	{
		if (active)
		{
			glBindVertexArray(m_ID);
		}
		else
		{
			glBindVertexArray(0);
		}
	}

	unsigned int VertexArray::GetVertexSize(BufferLayout layout)
	{
		switch (layout)
		{
		case Loco::BufferLayout::POS:
			return 3;
			break;
		case Loco::BufferLayout::POS_NORMAL:
			return 6;
			break;
		case Loco::BufferLayout::POS_NORMAL_TEX:
			return 8;
			break;
		case Loco::BufferLayout::POS_TEX:
			return 5;
			break;
		}
	}

}