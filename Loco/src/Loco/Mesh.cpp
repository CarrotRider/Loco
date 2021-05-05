#include "stdafx.h"
#include "Mesh.h"
#include "Loco/Renderer/VertexArray.h"
#include "Game.h"
#include "Camera.h"
#include "Loco/Renderer/Renderer.h"
#include "Loco/Renderer/Shader.h"
#include "Texture.h"
#include "Loco/Material.h"
#include "Loco/Mat_Default_Tex.h"
#include "Loco/Mat_Default_No_Tex.h"
#include "Loco/Components/DirLightComponent.h"
#include "Loco/Components/PointLightComponent.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Loco {

	Mesh::Mesh(Renderer* renderer, 
		const std::vector<Vertex>& vertices,
		const std::vector<unsigned>& indices,
		const std::shared_ptr<Material>& material)
		: m_Renderer(renderer)
		, m_Vertices(vertices)
		, m_Indices(indices)
		, m_Material(material)
	{	
		m_VAO = new VertexArray(m_Vertices.data(), m_Vertices.size(),
			m_Indices.data(), m_Indices.size(), BufferLayout::POS_NORMAL_TEX);
	}

	Mesh::~Mesh()
	{
		//delete m_VAO;
	}

	void Mesh::Draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
	{
		if (m_Material == nullptr)
		{
			std::cout << "Material is NULL" << std::endl;
			return;
		}
		Shader* shader = m_Material->GetShader();
		shader->Bind();
		
		// 设置 MVP
		shader->SetUniform("model", model);
		shader->SetUniform("view", view);
		shader->SetUniform("projection", projection);

		// 灯光信息已经在 Renderer 中统一进行设置

		// 设置材质信息
		if (m_Material->GetType() == MaterialType::PHONE_TEXTURE)
		{
			Mat_Default_Tex* material = dynamic_cast<Mat_Default_Tex*>(m_Material.get());
			shader->SetUniform("material.DiffuseTexutre_0", 0);
			shader->SetUniform("material.SpecularTexture_0", 1);
			shader->SetUniform("material.NormalTexture_0", 2);
			shader->SetUniform("material.Shininess", material->GetShininess());

			if (material->GetDiffuseTex() != nullptr)
			{
				material->GetDiffuseTex()->Active(0);
			}
			if (material->GetSpecularTex() != nullptr)
			{
				material->GetSpecularTex()->Active(1);
			}
			if (material->GetNormalTex() != nullptr)
			{
				material->GetNormalTex()->Active(2);
			}
		}
		else if (m_Material->GetType() == MaterialType::PHONG_SOILD_COLOR)
		{
			Mat_Default_No_Tex* material = dynamic_cast<Mat_Default_No_Tex*>(m_Material.get());
			shader->SetUniform("material.Diffuse", material->GetDiffuseColor());
			shader->SetUniform("material.Specular", material->GetSpecularColor());
			shader->SetUniform("material.Shininess", material->GetShininess());
		}
		else
		{
			std::cout << "ERROR::DO NOT SUPPORT MATERIAL" << std::endl;
		}

		glBindVertexArray(m_VAO->GetID());
		glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		shader->UnBind();
	}
}