#include "stdafx.h"
#include "RenderableComponent.h"
#include "Loco/Game.h"

namespace Loco {

	RenderableComponent::RenderableComponent(GameObject* owner, int updateOrder /*= 100*/)
		: Component(owner, updateOrder)
	{

	}

	Renderer* RenderableComponent::GetRenderer()
	{
		return GetGame()->GetRenderer();
	}

}