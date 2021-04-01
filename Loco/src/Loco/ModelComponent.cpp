#include "stdafx.h"
#include "ModelComponent.h"
#include "TransformComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Component.h"
#include "Camera.h"
#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Loco {

	ModelComponent::ModelComponent(GameObject* owner, 
		Model* model /*= nullptr*/, int updateOrder /*= 100*/)
		: RenderableComponent(owner, updateOrder)
		, m_Model(model)
		, m_Shader(nullptr)
	{
		GetRenderer()->AddRenderableComp(this);
	}

	ModelComponent::~ModelComponent()
	{
		GetRenderer()->RemoveRenderableComp(this);
	}

	void ModelComponent::OnUpdate(float deltaTime)
	{

	}

	void ModelComponent::OnDraw(Shader* shader)
	{

		if (m_Shader != nullptr)
		{
			shader = m_Shader;
		}

		glm::mat4 model(1.0f);
		model = glm::rotate(model, 
			glm::radians(GetOwner()->GetTransform()->GetRotation(DIR::X)), 
			glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model,
			glm::radians(GetOwner()->GetTransform()->GetRotation(DIR::Y)),
			glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model,
			glm::radians(GetOwner()->GetTransform()->GetRotation(DIR::Z)),
			glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, GetOwner()->GetTransform()->GetPosition());
		model = glm::scale(model, GetOwner()->GetTransform()->GetScale());

		glm::mat4 view = GetGame()->GetCamera()->GetViewMatrix();

		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(GetGame()->GetCamera()->Zoom),
			GetRenderer()->GetWindowWidth()/GetRenderer()->GetWindowHeight(), 0.1f, 100.0f);
		
		shader->Bind();

		shader->SetUniform("model", model);
		shader->SetUniform("view", view);
		shader->SetUniform("projection", projection);

		m_Model->Draw(shader);
		
		shader->UnBind();
	}

}