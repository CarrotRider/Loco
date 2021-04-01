#include <Loco.h>

using namespace Loco;

class MyGame : public Game
{
protected:
	bool InitializeGamePlay() override
	{
		go = new GameObject(this);
		go->AddComponent(new ModelComponent(go, new Model(m_Renderer, "assets/models/nanosuit.obj")));
		//go->GetTransform()->SetPosition(glm::vec3(10.0f, 10.0f, 10.0f));
		//go->GetTransform()->SetRotation(glm::vec3(30.0f, 0.0f, 0.0f));
		//go->GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
		light = new GameObject(this);
		ModelComponent* modelComp = new ModelComponent(light, new Model(m_Renderer, "assets/models/arrow.obj"));
		LightComponent* lightComp = new LightComponent(light);
		light->AddComponent(modelComp);
		light->AddComponent(lightComp);
		Shader* lightShader = new Shader("assets/shaders/light.vs", "assets/shaders/light.fs");
		modelComp->SetShader(lightShader);
		//lightComp->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		//light->GetTransform()->SetPosition(glm::vec3(10.0f, 10.0f, 10.0f));
		light->GetTransform()->SetRotation(glm::vec3(50.0f, -30.0f, 0.0f));
		return true;
	}
private:
	GameObject* go;
	GameObject* light;
};

Loco::Game* Loco::CreateGame()
{
	return new MyGame();
}