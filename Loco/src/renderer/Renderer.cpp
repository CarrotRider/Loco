#include "stdafx.h"
#include "Renderer.h"

#include "Game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Loco {

	Renderer::Renderer(Game* game)
		: m_Game(game)
	{
		
	}

	Renderer::~Renderer()
	{

	}

	bool Renderer::Initialize(float width, float height)
	{
		m_Width = width;
		m_Height = height;
		if (!glfwInit())
			return -1;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(width, height, "Loco", nullptr, nullptr);;

		if (!m_Window)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		//
		m_Model = new Model("assets/models/nanosuit.obj");
		shader = new Shader("assets/shaders/model_test.vs", "assets/shaders/model_test.fs");

		glEnable(GL_DEPTH_TEST);
	}

	void Renderer::ShutDown()
	{
		delete m_Window;
		delete m_Model;
		delete shader;
		glfwTerminate();
	}

	void Renderer::Draw(float deltaTime)
	{
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->Active();

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glm::mat4 view = GetGame()->GetCamera()->GetViewMatrix();
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(GetGame()->GetCamera()->Zoom), float(m_Width / m_Height), 0.1f, 100.0f);

		shader->SetUniform("model", model);
		shader->SetUniform("view", view);
		shader->SetUniform("projection", projection);

		m_Model->Draw(shader);

		glfwSwapBuffers(m_Window);
	}

	void Renderer::LoadTexture(const std::string& fileName, Texture::Type type)
	{
		m_Textures.insert(std::pair<std::string, std::unique_ptr<Texture>>(fileName,
			std::move(std::make_unique<Texture>(fileName, type))));
	}

	Texture* Renderer::GetTexture(const std::string& fileName) const
	{
		auto iter = m_Textures.find(fileName);
		return iter == m_Textures.end() ? nullptr : (*iter).second.get();
	}

	void Renderer::AddSpriteComp(const SpriteComponent* spriteComp)
	{

	}

	void Renderer::RemoveSpriteComp(const SpriteComponent* spriteComp)
	{

	}

}
