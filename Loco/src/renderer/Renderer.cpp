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
		vao = new VertexArray(vertices, 36, indices, 6);
		texture_1 = new Texture("assets/textures/container.jpg");
		texture_2 = new Texture("assets/textures/awesomeface.png");
		texture_1->Active(0);
		texture_2->Active(1);
		shader = new Shader("assets/shaders/test.vs", "assets/shaders/test.fs");
		shader->Active();
		shader->SetUniform("texture1", 0);
		shader->SetUniform("texture2", 1);
		glEnable(GL_DEPTH_TEST);
	}

	void Renderer::ShutDown()
	{
		delete m_Window;
		delete vao;
		delete texture_1;
		delete texture_2;
		delete shader;
		glfwTerminate();
	}

	void Renderer::Draw(float deltaTime)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->Active();
		glm::mat4 model(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		glm::mat4 view = GetGame()->GetCamera()->GetViewMatrix();

		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(GetGame()->GetCamera()->Zoom), float(m_Width / m_Height), 0.1f, 100.0f);

		shader->SetUniform("model", model);
		shader->SetUniform("view", view);
		shader->SetUniform("projection", projection);

		vao->SetActive(true);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		vao->SetActive(false);

		glfwSwapBuffers(m_Window);
	}

	Texture* Renderer::GetTexture(const std::string& fileName) const
	{
		return nullptr;
	}

	void Renderer::AddSpriteComp(const SpriteComponent* spriteComp)
	{

	}

	void Renderer::RemoveSpriteComp(const SpriteComponent* spriteComp)
	{

	}

}
