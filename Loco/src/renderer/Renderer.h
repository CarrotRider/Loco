#pragma once

#include "Texture.h"

class Game;

namespace Loco {

	class Renderer
	{
	public:
		Renderer(Game* game);
		~Renderer();

		Game* GetGame() const { return m_Game; }

		Texture* GetTexture(const std::string& fileName) const;
	private:
		Game* m_Game;

		// resources
		std::unordered_map<std::string, Texture*> m_Textures;
	};
}



