#pragma once
#include "RenderableComponent.h"


namespace Loco {

	class Model;

	class ModelComponent :
		public RenderableComponent
	{
	public:
		ModelComponent(GameObject* owner, Model* model = nullptr,int updateOrder = 100);
		virtual ~ModelComponent() override;

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnDraw(Shader* shader) override;

		void SetModel(Model* model) { m_Model = model; }
		Model* GetModel() { return m_Model; }
	protected:
		Model* m_Model;
	};

}



