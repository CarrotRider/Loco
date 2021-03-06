#include <Loco.h>

using namespace Loco;

class MyGame : public Game
{
public:
	virtual ~MyGame()
	{
		//delete go;
		// delete dirLight;
		//delete pointLight;
	}
protected:
	bool InitializeGamePlay() override
	{
		go = new GameObject(this);
		go->AddComponent(new ModelComponent(go, new Model(m_Renderer, "assets/models/untitled.fbx")));
		go->GetTransform()->SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
		ground = new GameObject(this);
		ground->AddComponent(new ModelComponent(ground, new Model(m_Renderer, "assets/models/wood_ground.obj")));
		wall = new GameObject(this);
		wall->AddComponent(new ModelComponent(wall, new Model(m_Renderer, "assets/models/wall.obj")));
		wall->GetTransform()->SetPosition(glm::vec3(10.0f, 5.0f, -10.0f));
		wall->GetTransform()->SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));

		//go->GetTransform()->SetPosition(glm::vec3(10.0f, 10.0f, 10.0f));
		//go->GetTransform()->SetRotation(glm::vec3(30.0f, 0.0f, 0.0f));
		//go->GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));

		//dirLight = new GameObject(this);
		//ModelComponent* modelComp = new ModelComponent(dirLight, new Model(m_Renderer, "assets/models/arrow.obj"));
		//DirLightComponent* lightComp = new DirLightComponent(dirLight);
		//dirLight->AddComponent(modelComp);
		//dirLight->AddComponent(lightComp);
		//Shader* lightShader = GetRenderer()->GetShader("light.vs", "light.fs").get();
		//modelComp->SetShader(lightShader);
		////lightComp->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		////light->GetTransform()->SetPosition(glm::vec3(10.0f, 10.0f, 10.0f));
		//dirLight->GetTransform()->SetRotation(glm::vec3(50.0f, -30.0f, 0.0f));

		pointLight = new GameObject(this);
		//ModelComponent* modelPointComp = new ModelComponent(pointLight, new Model(m_Renderer, "assets/models/default_sphere.obj"));
		PointLightComponent* pointLightComp = new PointLightComponent(pointLight);
		//pointLight->AddComponent(modelPointComp);
		pointLight->AddComponent(pointLightComp);
		//modelPointComp->SetShader(lightShader);
		pointLight->GetTransform()->SetPosition(glm::vec3(10.0f, 10.0f, 10.0f));

		return true;
	}
private:
	GameObject* go;
	GameObject* ground;
	GameObject* wall;
	// GameObject* dirLight;
	GameObject* pointLight;
};

Loco::Game* Loco::CreateGame()
{
	return new MyGame();
}