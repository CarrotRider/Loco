#include "stdafx.h"
#include "Mesh.h"
#include "Loco/Renderer/VertexArray.h"
#include "Game.h"
#include "Loco/Renderer/Renderer.h"
#include "Loco/Renderer/Shader.h"
#include "Texture.h"

#include <glad/glad.h>

namespace Loco {

	Mesh::Mesh(Renderer* renderer, std::vector<Vertex> vertices, 
		std::vector<unsigned> indices, 
		std::vector<std::string> texturesKeys)
		: m_Renderer(renderer)
	{
		this->m_Vertices = vertices;
		this->m_Indices = indices;
		this->m_TextureKeys = texturesKeys;
		
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

		std::string diffName = "material.SpecularTexuter_";
		std::string specName = "material.SpecularTexuter_";
		std::string normName = "material.NormalTexuter_";

		for (unsigned i = 0; i < m_TextureKeys.size(); i++)
		{
			Texture* tex = m_Renderer->GetTexture(m_TextureKeys[i]);
			std::string name, idx;
			Texture::Type type = tex->GetType();
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
			tex->Active(i);
			shader->SetUniform(name + idx, i);
		}
		shader->SetUniform("material.Shininess", 32.0f);

		glBindVertexArray(m_VAO->GetID());
		glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}