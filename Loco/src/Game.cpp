#include "stdafx.h"
#include "Game.h"

namespace Loco {

	Game::Game()
		:m_GameState(GameState::RUNNING)
		,m_Renderer(nullptr)
		,m_UpdatingGameObj(false)
	{

	}

	Game::~Game()
	{

	}

	bool Game::Initialize()
	{
		return false;
	}

	void Game::Loop()
	{
		if (m_GameState != GameState::PAUSE)
		{
			ProcessInput();
			GameUpdate();
			Output();
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

	void Game::ProcessInput()
	{
		// todo
	}

	void Game::GameUpdate()
	{
		//todo: 计算 deltaTime
		float deltaTime = 0.5f;

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

	void Game::Output()
	{
		// todo
	}

}