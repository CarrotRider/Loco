#include "stdafx.h"
#include "Game.h"
#include "GameObject.h"
#include "Loco/Renderer/Renderer.h"
#include "WindowsWindow.h"
#include "Camera.h"
#include "Loco/Components/ModelComponent.h"
#include "Loco/Events/AppEvent.h"
#include "Loco/Events/KeyEvent.h"
#include "Loco/Events/MouseEvent.h"


namespace Loco {
	
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
	}

	bool Game::Initialize()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(
			std::bind(&Game::OnEvent, this, std::placeholders::_1));

		m_Renderer = new Renderer(this);
		if (!m_Renderer->Initialize(980.0f, 540.0f))
		{
			std::cout << "Failed to initialize renderer" << std::endl;
			delete m_Renderer;
			m_Renderer = nullptr;
			return false;
		}

		if (!InitializeGamePlay())
		{
			std::cout << "Faill to Load Game" << std::endl;
			return false;
		}
		//
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

	void Game::OnEvent(Event& event)
	{
		switch (event.GetEventType())
		{
		case EventType::WINDOW_CLOSE:
			SetGameState(GameState::QUIT);
			break;
		case EventType::WINDOW_RESIZE:
			glViewport(0, 0, static_cast<WindowResizeEvent&>(event).GetWidth(), static_cast<WindowResizeEvent&>(event).GetHeight());
			break;
		case EventType::MOUSE_MOVED:
		{
			MouseMovedEvent& mme = static_cast<MouseMovedEvent&>(event);
			if (firstMouse)
			{
				lastX = mme.GetX();
				lastY = mme.GetY();
				firstMouse = false;
			}
			float xOffset = mme.GetX() - lastX;
			float yOffset = mme.GetY() - lastY;
			lastX = mme.GetX();
			lastY = mme.GetY();
			m_Camera->ProcessMouseMovement(xOffset, -yOffset);
			break;
		}
		case EventType::MOUSE_SCROLLED:
			m_Camera->ProcessMouseScroll(static_cast<MouseScrolledEvent&>(event).GetYOffset());
			break;
		}
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
		GLFWwindow* window = (GLFWwindow*)m_Window->GetNativeWindow();

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
		m_Window->OnUpdate();
	}

}