#include "stdafx.h"
#include "RenderableComponent.h"
#include "Game.h"

namespace Loco {

	RenderableComponent::RenderableComponent(GameObject* owner, int updateOrder /*= 100*/)
		: Component(owner, updateOrder)
	{

	}

	Loco::Renderer* RenderableComponent::GetRenderer()
	{
		return GetGame()->GetRenderer();
	}

}