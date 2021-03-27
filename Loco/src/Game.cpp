#include "stdafx.h"
#include "Game.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Camera.h"
#include "ModelComponent.h"


namespace Loco {

	Game* Game::instance = nullptr;
	
	Game::Game()
		: m_GameState(GameState::RUNNING)
		, m_Renderer(nullptr)
		, m_UpdatingGameObj(false)
		, m_TickCounts(0)
		, m_Camera(nullptr)
	{
		m_Camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	}


	Game::~Game()
	{
		delete m_Camera;
		delete m_Renderer;
		delete Game::instance;
	}

	bool Game::Initialize()
	{
		m_Renderer = new Renderer(this);
		if (!m_Renderer->Initialize(980.0f, 540.0f))
		{
			std::cout << "Failed to initialize renderer" << std::endl;
			delete m_Renderer;
			m_Renderer = nullptr;
			return false;
		}
		glfwSetWindowCloseCallback(GetRenderer()->GetWindow(),
			[](GLFWwindow* window) {
				Game::GetInstance()->SetGameState(GameState::QUIT);
			});
		glfwSetFramebufferSizeCallback(GetRenderer()->GetWindow(), 
			[](GLFWwindow* window, int width, int height) {
				glViewport(0, 0, width, height);
			});
		glfwSetCursorPosCallback(GetRenderer()->GetWindow(),
			[](GLFWwindow* window, double xPos, double yPos) {
				if (Game::GetInstance()->firstMouse)
				{
					Game::GetInstance()->lastX = xPos;
					Game::GetInstance()->lastY = yPos;
					Game::GetInstance()->firstMouse = false;
				}

				float xOffset = xPos - Game::GetInstance()->lastX;
				float yOffset = yPos - Game::GetInstance()->lastY;
				Game::GetInstance()->lastX = xPos;
				Game::GetInstance()->lastY = yPos;

				Game::GetInstance()->m_Camera->ProcessMouseMovement(xOffset, -yOffset);
			});
		glfwSetScrollCallback(GetRenderer()->GetWindow(), 
			[](GLFWwindow* window, double xOffset, double yOffset) {
				Game::GetInstance()->GetCamera()->ProcessMouseScroll(yOffset);
			});

		//
		go = new GameObject(this);
		go->AddComponent(new ModelComponent(go, new Model("assets/models/nanosuit.obj")));
		//go->GetTransform()->SetPosition(glm::vec3(10.0f, 10.0f, 10.0f));
		//go->GetTransform()->SetRotation(glm::vec3(30.0f, 0.0f, 0.0f));
		//go->GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
		light = new GameObject(this);
		ModelComponent* modelComp = new ModelComponent(light, new Model("assets/models/arrow.obj"));
		LightComponent* lightComp = new LightComponent(light);
		light->AddComponent(modelComp);
		light->AddComponent(lightComp);
		Shader* lightShader = new Shader("assets/shaders/light.vs", "assets/shaders/light.fs");
		modelComp->SetShader(lightShader);
		//lightComp->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		//light->GetTransform()->SetPosition(glm::vec3(10.0f, 10.0f, 10.0f));
		light->GetTransform()->SetRotation(glm::vec3(-45.0f, -45.0f, -45.0f));


		return true;
	}

	void Game::Loop()
	{
		//todo: 计算 deltaTime
		float currentFrame = glfwGetTime();
		float deltaTime = currentFrame - m_TickCounts;
		m_TickCounts = currentFrame;

		while (m_GameState == GameState::RUNNING)
		{
			ProcessInput(deltaTime);
			GameUpdate(deltaTime);
			Output(deltaTime);
		}
	}

	void Game::ShutDown()
	{

	}

	void Game::AddGameObject(GameObject* go)
	{
		if (m_UpdatingGameObj)
		{
			m_PendingGameObjs.emplace_back(go);
		}
		else
		{
			m_GameObjs.emplace_back(go);
		}
	}

	void Game::RemoveGameObject(GameObject* go)
	{
		auto iter = std::find(m_PendingGameObjs.begin(), m_PendingGameObjs.end(), go);
		if (iter != m_PendingGameObjs.end())
		{
			std::iter_swap(iter, m_PendingGameObjs.end() - 1);
			m_PendingGameObjs.pop_back();
			return;
		}
		iter = std::find(m_GameObjs.begin(), m_GameObjs.end(), go);
		if (iter != m_GameObjs.end())
		{
			std::iter_swap(iter, m_GameObjs.end() - 1);
			m_GameObjs.pop_back();
		}
	}

	void Game::ProcessInput(float deltaTime)
	{
		GLFWwindow* window = GetRenderer()->GetWindow();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			this->SetGameState(GameState::QUIT);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			m_Camera->ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			m_Camera->ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			m_Camera->ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			m_Camera->ProcessKeyboard(RIGHT, deltaTime);

		glfwPollEvents();
	}

	void Game::GameUpdate(float deltaTime)
	{
		if (m_GameState == GameState::RUNNING)
		{
			m_UpdatingGameObj = true;
			for (auto& go : m_GameObjs)
			{
				go->OnUpdate(deltaTime);
			}
			m_UpdatingGameObj = false;
		}
		for (auto& go : m_PendingGameObjs)
		{
			m_GameObjs.emplace_back(go);
		}
		m_PendingGameObjs.clear();
	}

	void Game::Output(float deltaTime)
	{
		m_Renderer->Draw(deltaTime);
	}

}