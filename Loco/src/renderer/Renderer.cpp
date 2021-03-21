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

		glEnable(GL_DEPTH_TEST);

		initAxis();

		//
		m_Model = new Model("assets/models/nanosuit.obj");
		shader = new Shader("assets/shaders/model_test.vs", "assets/shaders/model_test.fs");
		
		
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

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glm::mat4 view = GetGame()->GetCamera()->GetViewMatrix();
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(GetGame()->GetCamera()->Zoom), 
			float(m_Width / m_Height), 0.1f, 100.0f);

		drawAxis(view, projection);

		shader->Active();

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

	void Renderer::initAxis()
	{
		m_VAO_Axis = std::make_unique<VertexArray>((float*)m_Vecs_Axis, 6,
			m_Indices_Axis, 6, BufferLayout::POS);
		m_Shader_Axis = std::make_unique<Shader>("./assets/shaders/axis.vs",
			"./assets/shaders/axis.fs");
	}

	void Renderer::drawAxis(const glm::mat4& view, const glm::mat4& projection) const
	{
		m_Shader_Axis->Active();

		m_Shader_Axis->SetUniform("view", view);
		m_Shader_Axis->SetUniform("projection", projection);

		m_VAO_Axis->SetActive(true);

		m_Shader_Axis->SetUniform("color", glm::vec3(1.0f, 0.0f, 0.0f));
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
		m_Shader_Axis->SetUniform("color", glm::vec3(0.0f, 1.0f, 0.0f));
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(2 * sizeof(float)));
		m_Shader_Axis->SetUniform("color", glm::vec3(0.0f, 0.0f, 1.0f));
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(4 * sizeof(float)));
		
		m_VAO_Axis->SetActive(false);
		
		m_Shader_Axis->UnActive();
	}

}
