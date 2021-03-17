#include "stdafx.h"
#include "SpriteComponent.h"

#include "Game.h"
#include "Renderer.h"
#include "GameObject.h"


namespace Loco {

	SpriteComponent::SpriteComponent(GameObject* owner, int drawOrder /*= 100*/)
		: Component(owner)
		, m_Texture(nullptr)
		, m_Visible(true)
		, m_DrawOrder(drawOrder)
		, m_TexWidth(0)
		, m_TexHeight(0)
	{
		m_Owner->GetGame()->GetRenderer()->AddSpriteComp(this);
	}

	SpriteComponent::~SpriteComponent()
	{
		m_Owner->GetGame()->GetRenderer()->RemoveSpriteComp(this);
	}

	void SpriteComponent::Draw(Shader* shader)
	{
		if (m_Texture)
		{
			// todo
			// 计算 model 矩阵
			// 设置 model 矩阵
			// shader->SetUniform();
			m_Texture->Active();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	}

	void SpriteComponent::SetTexture(Texture* texture)
	{
		m_Texture = texture;
		m_TexWidth = texture->Width();
		m_TexHeight = texture->Height();
	}

}
