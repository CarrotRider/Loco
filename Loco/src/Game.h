#pragma once


namespace Loco {

	class Renderer;
	class Window;
	class Camera;
	class Event;
	class GameObject;

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

		void OnEvent(Event& event);

		void AddGameObject(GameObject*);
		void RemoveGameObject(GameObject* gameObj);

		Window& GetWindow() const { return *m_Window; }
		Renderer* GetRenderer() const { return m_Renderer; }
		Camera* GetCamera() const { return m_Camera; }

		void SetGameState(GameState state) { m_GameState = state; }
		GameState GetGameState() { return m_GameState; }
	protected:
		virtual bool InitializeGamePlay() { return true; }

		void ProcessInput(float deltaTime);
		void GameUpdate(float deltaTime);
		void Output(float deltaTime);
	protected:
		GameState m_GameState;

		bool m_UpdatingGameObj;
		int m_TickCounts;
		std::vector<GameObject*> m_GameObjs;
		std::vector<GameObject*> m_PendingGameObjs;

		Renderer* m_Renderer;
		std::unique_ptr<Window> m_Window;
		//
		Camera* m_Camera;
		bool firstMouse = true;

		float lastX = 0.0f;
		float lastY = 0.0f;
	};

	// 由客户程序实现
	Game* CreateGame();
}



