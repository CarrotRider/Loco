#pragma once

#include "VertexArray.h"
#include "Texture.h"
#include "Model.h"
#include "SpriteComponent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Loco {

	class Game;

	class Renderer
	{
	public:
		Renderer(Game* game);
		~Renderer();

		bool Initialize(float width, float height);
		void ShutDown();

		void Draw(float deltaTime);

		Game* GetGame() const { return m_Game; }
		GLFWwindow* GetWindow() const { return m_Window; }

		// resources
		void LoadTexture(const std::string& fileName, Texture::Type type);
		Texture* GetTexture(const std::string& fileName) const;
		// components
		void AddSpriteComp(const SpriteComponent* spriteComp);
		void RemoveSpriteComp(const SpriteComponent* spriteComp);
	private:
		void initAxis();
		void drawAxis(const glm::mat4& view, const glm::mat4& projection) const;
	private:
		Game* m_Game;
		GLFWwindow* m_Window;
		float m_Width;
		float m_Height;
		// resources
		std::unordered_map<std::string, std::unique_ptr<Texture>> m_Textures;
		// components
		std::vector<SpriteComponent*> m_SpriteComps;

		// Axis
		const glm::vec3 m_Vecs_Axis[6] {
			glm::vec3(-500.0f, 0.0f, 0.0f), glm::vec3(500.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, -500.0f, 0.0f), glm::vec3(0.0f, 500.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, -500.0f), glm::vec3(0.0f, 0.0f, 500.0f),
		};
		const unsigned m_Indices_Axis[6]{ 0, 1, 2, 3, 4, 5 };
		std::unique_ptr<VertexArray> m_VAO_Axis;
		std::unique_ptr<Shader> m_Shader_Axis;

		//
		Shader* shader;
		Model* m_Model;
	};
}



