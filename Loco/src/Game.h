#pragma once

#include "GameObject.h"
#include "Renderer.h"

namespace Loco {

	enum class GameState 
	{
		RUNNING, PAUSE, QUIT
	};

	class Game
	{
	public:
		Game();
		virtual ~Game();
		bool Initialize();
		void Loop();
		void ShutDown();

		void AddGameObject(GameObject*);
		void RemoveGameObject(GameObject* gameObj);

		Renderer* GetRenderer() { return m_Renderer; }
	private:
		void ProcessInput();
		void GameUpdate();
		void Output();
	private:
		GameState m_GameState;

		bool m_UpdatingGameObj;
		std::vector<GameObject*> m_GameObjs;
		std::vector<GameObject*> m_PendingGameObjs;

		Renderer* m_Renderer;

	};

}



