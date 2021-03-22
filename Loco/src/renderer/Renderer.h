#pragma once

#include "VertexArray.h"
#include "Texture.h"
#include "Model.h"
#include "RenderableComponent.h"

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

		// components
		void AddRenderableComp(RenderableComponent* renderableComp);
		void RemoveRenderableComp(RenderableComponent* renderableComp);
		// resources
		void LoadTexture(const std::string& fileName, 
			Texture::Type type = Texture::Type::NONE);
		Texture* GetTexture(const std::string& fileName) const;
		void LoadModel(const std::string& fileName);
		Model* GetModel(const std::string& fileName) const;

		// Getter & Setter
		void SetWindowWidth(float width) { m_Width = width; }
		float GetWindowWidth() { return m_Width; }
		void SetWindowHeight(float height) { m_Height = height; }
		float GetWindowHeight() { return m_Height; }

	private:
		void initAxis();
		void drawAxis() const;
	private:
		Game* m_Game;
		GLFWwindow* m_Window;
		float m_Width;
		float m_Height;

		// components
		std::vector<RenderableComponent*> m_RenderebleComps;
		// resources
		std::unordered_map<std::string, std::unique_ptr<Texture>> m_Textures;
		std::unordered_map<std::string, std::unique_ptr<Model>> m_Models;


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
		//Model* m_Model;
	};
}



