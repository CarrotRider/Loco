#include "stdafx.h"
#include "VertexArray.h"

#include "glad/glad.h"

namespace Loco {

	VertexArray::VertexArray(const float* verts, unsigned int numVerts, 
		const unsigned int* indices, unsigned int numIndices)
		: m_NumVerts(numVerts)
		, m_NumIndices(numIndices)
		, m_ID(0), m_ID_VBO(0), m_ID_EBO(0)
	{
		glGenVertexArrays(1, &m_ID);
		glBindVertexArray(m_ID);
		
		glGenBuffers(1, &m_ID_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID_VBO);
		glBufferData(GL_ARRAY_BUFFER, 
			numVerts * 5 * sizeof(float), verts, GL_STATIC_DRAW);

		//glGenBuffers(1, &m_ID_EBO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID_EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
		//	numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		//Layout 临时
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
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

}