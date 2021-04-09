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

		for (unsigned i = 0; i < m_TextureKeys.size(); i++)
		{
			Texture* tex = m_Renderer->GetTexture(m_TextureKeys[i]);
			Texture::Type type = tex->GetType();
			if (type == Texture::Type::DIFFUSE)
			{
				tex->Active(0);
			}
			else if (type == Texture::Type::SPECULAR)
			{
				tex->Active(1);
			}
			else if (type == Texture::Type::NORMAL)
			{
				tex->Active(2);
			}
		}
		shader->SetUniform("material.DiffuseTexutre_0", 0);
		shader->SetUniform("material.SpecularTexture_0", 1);
		shader->SetUniform("material.NormalTexture_0", 2);
		shader->SetUniform("material.Shininess", 32.0f);

		glBindVertexArray(m_VAO->GetID());
		glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}