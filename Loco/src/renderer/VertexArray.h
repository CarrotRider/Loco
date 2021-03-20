#pragma once
#include "Mesh.h"

namespace Loco
{
	enum class BufferLayout
	{
		POS, POS_NORMAL, POS_NORMAL_TEX, POS_TEX
	};
	class VertexArray
	{
	public:
		VertexArray(const  Mesh::Vertex* verts, unsigned int numVerts,
			const unsigned int* indices, unsigned int numIndices,
			BufferLayout layout);
		VertexArray(const float* verts, unsigned int numVerts,
			const unsigned int* indices, unsigned int numIndices,
			BufferLayout layout);
		~VertexArray();

		void SetActive(bool active);

		unsigned int GetVertexNum() const { return m_NumVerts; }
		unsigned int GetIndexNum() const { return m_NumIndices; }

		static unsigned int GetVertexSize(BufferLayout layout);

		unsigned int GetID() const { return m_ID; }
		unsigned int GetID_VBO() const { return m_ID_VBO; }
		unsigned int GetID_EBO() const { return m_ID_EBO; }
	private:
		unsigned int m_ID;

		unsigned int m_ID_VBO;
		unsigned int m_ID_EBO;

		unsigned int m_NumVerts;
		unsigned int m_NumIndices;
	};
}



