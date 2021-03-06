#pragma once
#include "Loco/Core.h"
#include "RenderableComponent.h"


namespace Loco {

	class Model;

	class LOCO_API ModelComponent :
		public RenderableComponent
	{
	public:
		ModelComponent(GameObject* owner, Model* model = nullptr,int updateOrder = 100);
		virtual ~ModelComponent() override;

		virtual void OnUpdate(float deltaTime) override;
		virtual void Draw() override;

		void SetModel(Model* model) { m_Model = model; }
		Model* GetModel() { return m_Model; }
		void SetShader(Shader* shader) { m_Shader = shader; }
		Shader* GetShader() { return m_Shader; }
	protected:
		Model* m_Model;
		Shader* m_Shader;
	};

}



