#pragma once

namespace Loco
{
	class VertexArray
	{
	public:
		VertexArray(const float* verts, unsigned int numVerts,
			const unsigned int* indices, unsigned int numIndices);
		~VertexArray();

		void SetActive(bool active);

		unsigned int GetVertexNum() const { return m_NumVerts; }
		unsigned int GetIndexNum() const { return m_NumIndices; }
	private:
		unsigned int m_ID;

		unsigned int m_ID_VBO;
		unsigned int m_ID_EBO;

		unsigned int m_NumVerts;
		unsigned int m_NumIndices;
	};
}



