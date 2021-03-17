#pragma once

#include "GameObject.h"
#include "Renderer.h"
#include "Camera.h"

namespace Loco {

	enum class GameState 
	{
		RUNNING, PAUSE, QUIT
	};

	class Game
	{
	private:
		Game();
		static Game* instance;
	public:
		static Game* GetInstance()
		{
			if (instance == nullptr)
				instance = new Game();
			return instance;
		}
		virtual ~Game();
		bool Initialize();
		void Loop();
		void ShutDown();

		void AddGameObject(GameObject*);
		void RemoveGameObject(GameObject* gameObj);

		Renderer* GetRenderer() const { return m_Renderer; }
		Camera* GetCamera() const { return m_Camera; }

		void SetGameState(GameState state) { m_GameState = state; }
		GameState GetGameState() { return m_GameState; }
	private:
		void ProcessInput(float deltaTime);
		void GameUpdate(float deltaTime);
		void Output(float deltaTime);
	private:
		GameState m_GameState;

		bool m_UpdatingGameObj;
		int m_TickCounts;
		std::vector<GameObject*> m_GameObjs;
		std::vector<GameObject*> m_PendingGameObjs;

		Renderer* m_Renderer;
		//
		Camera* m_Camera;
		bool firstMouse = true;

		float lastX = 0.0f;
		float lastY = 0.0f;
		//
	};
}



