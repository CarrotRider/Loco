#include "stdafx.h"
#include "Mesh.h"
#include "VertexArray.h"

#include <glad/glad.h>

namespace Loco {

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture*> textures)
	{
		this->m_Vertices = vertices;
		this->m_Indices = indices;
		this->m_Textures = textures;
		
		m_VAO = new VertexArray(m_Vertices.data(), m_Vertices.size(),
			m_Indices.data(), m_Indices.size(), BufferLayout::POS_NORMAL_TEX);
	}

	Mesh::~Mesh()
	{
		//delete m_VAO;
	}

	void Mesh::Draw(Shader* shader)
	{
		unsigned int diffuseIdx = 0;
		unsigned int specularIdx = 0;
		unsigned int normalIdx = 0;

		std::string diffName = "texture_diffuse";
		std::string specName = "texture_specular";
		std::string normName = "texture_normal";
		for (unsigned int i = 0; i < m_Textures.size(); i++)
		{
			std::string name, idx;
			Texture::Type type = m_Textures[i]->GetType();
			if (type == Texture::Type::DIFFUSE)
			{
				name = diffName;
				idx = std::to_string(diffuseIdx++);
			}
			else if (type == Texture::Type::SPECULAR)
			{
				name = specName;
				idx = std::to_string(specularIdx++);
			}
			else if (type == Texture::Type::NORMAL)
			{
				name = normName;
				idx = std::to_string(normalIdx++);
			}
			m_Textures[i]->Active(i);
			shader->SetUniform(name + idx, i);
		}

		glBindVertexArray(m_VAO->GetID());
		glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}