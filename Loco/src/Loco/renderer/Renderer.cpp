#include "stdafx.h"
#include "Renderer.h"
#include "FrameBuffer.h"
#include "RenderBuffer.h"
#include "Camera.h"
#include "Game.h"
#include "CubeTexture.h"


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

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		// Init Frame Buffer
		m_FrameBuffer = new FrameBuffer();

		m_ScreenTexture = new Texture(m_Width, m_Height);
		m_FrameBuffer->BindTexture(*m_ScreenTexture, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D);

		m_RenderBuffer = new RenderBuffer(GL_DEPTH24_STENCIL8, m_Width, m_Height);
		m_FrameBuffer->BindRenderBuffer(*m_RenderBuffer);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		}
		m_FrameBuffer->UnBind();

		// Pass Final
		m_ScreenVA = new VertexArray(m_ScreenPanel, 6, m_Indices_Screen, 6, 
			BufferLayout::POS_TEX);
		m_ShaderFinal = new Shader("assets/shaders/final_pass.vs",
			"assets/shaders/final_pass.fs");

		// Init Scene
		initAxis();
		initSkybox();

		// Init Custom
		m_ShaderDefault = new Shader("assets/shaders/default.vs", 
			"assets/shaders/default.fs");
	}

	void Renderer::ShutDown()
	{	
		delete m_ScreenVA;
		delete m_FrameBuffer;
		delete m_ScreenTexture;
		delete m_RenderBuffer;
		delete m_ShaderFinal;

		//
		delete m_ShaderDefault;
		glfwTerminate();
	}

	void Renderer::Draw(float deltaTime)
	{
		// Pass One
		m_FrameBuffer->Bind();
		
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		drawSkybox();
		drawAxis();

		m_ShaderDefault->Bind();
		m_ShaderDefault->SetUniform("viewPos", GetGame()->GetCamera()->Position);
		
		int len = m_LightComps.size();
		std::string s0 = "dirLights[";
		std::string s1 = "].Position";
		std::string s2 = "].Direction";
		std::string s3 = "].Color";
		for (int i = 0; i < len; i++)
		{
			std::string idx = std::to_string(i);
			m_ShaderDefault->SetUniform(s0 + idx + s1, m_LightComps[i]->GetPosition());
			m_ShaderDefault->SetUniform(s0 + idx + s2, m_LightComps[i]->GetDirection());
			m_ShaderDefault->SetUniform(s0 + idx + s3, m_LightComps[i]->GetColor());
		}

		for (auto& renderableComp : m_RenderebleComps)
		{
			renderableComp->OnDraw(m_ShaderDefault);
		}

		// Pass Final
		m_FrameBuffer->UnBind();
		
		glDisable(GL_DEPTH_TEST);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		m_ShaderFinal->Bind();
		m_ScreenVA->SetActive(true);
		m_ScreenTexture->Active(0);
		m_ShaderFinal->SetUniform("screenTexture", 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		m_ScreenTexture->UnBind();
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

	void Renderer::LoadModel(const std::string& fileName)
	{
		m_Models.insert(std::pair<std::string, std::unique_ptr<Model>>(fileName,
			std::move(std::make_unique<Model>(this ,fileName))));
	}

	Model* Renderer::GetModel(const std::string& fileName) const
	{
		auto iter = m_Models.find(fileName);
		return iter == m_Models.end() ? nullptr : (*iter).second.get();
	}

	void Renderer::AddRenderableComp(RenderableComponent* renderableComp)
	{
		m_RenderebleComps.push_back(renderableComp);
	}

	void Renderer::RemoveRenderableComp(RenderableComponent* renderableComp)
	{
		auto iter = std::find(m_RenderebleComps.begin(), m_RenderebleComps.end(), 
			renderableComp);
		if (iter != m_RenderebleComps.end())
		{
			m_RenderebleComps.erase(iter);
		}
	}

	void Renderer::AddLightComp(LightComponent* lightComp)
	{
		m_LightComps.push_back(lightComp);
	}

	void Renderer::RemoveLightComp(LightComponent* lightComp)
	{
		auto iter = std::find(m_LightComps.begin(), m_LightComps.end(), lightComp);
		if (iter != m_LightComps.end())
		{
			m_LightComps.erase(iter);
		}
	}

	void Renderer::initAxis()
	{
		m_VAO_Axis = std::make_unique<VertexArray>((float*)m_Vecs_Axis, 6,
			m_Indices_Axis, 6, BufferLayout::POS);
		m_Shader_Axis = std::make_unique<Shader>("./assets/shaders/axis.vs",
			"./assets/shaders/axis.fs");
	}

	void Renderer::drawAxis() const
	{
		glm::mat4 view = GetGame()->GetCamera()->GetViewMatrix();
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(GetGame()->GetCamera()->Zoom),
			float(m_Width / m_Height), 0.1f, 1000.0f);

		m_Shader_Axis->Bind();

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
		
		m_Shader_Axis->UnBind();
	}

	void Renderer::initSkybox()
	{
		m_VAO_Skybox = std::make_unique<VertexArray>(m_Vecs_Skybox, 36,
			m_Indices_Axis, 26, BufferLayout::POS);
		m_Shader_Skybox = std::make_unique<Shader>("./assets/shaders/sky_box.vs",
			"./assets/shaders/sky_box.fs");
		m_CubeTexture = std::make_unique<CubeTexture>();
		m_CubeTexture->Load(m_SkyboxTexPaths);
	}

	void Renderer::drawSkybox() const
	{
		glm::mat4 model(1.0f);
		model = glm::scale(model, glm::vec3(500.0f, 500.0f, 500.0f));
		glm::mat4 view = GetGame()->GetCamera()->GetViewMatrix();
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(GetGame()->GetCamera()->Zoom),
			float(m_Width / m_Height), 0.1f, 1000.0f);

		m_Shader_Skybox->Bind();

		m_Shader_Skybox->SetUniform("model", model);
		m_Shader_Skybox->SetUniform("view", view);
		m_Shader_Skybox->SetUniform("projection", projection);

		glDepthMask(GL_FALSE);
		m_VAO_Skybox->SetActive(true);

		m_CubeTexture->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		m_VAO_Skybox->SetActive(false);
		glDepthMask(GL_TRUE);

		m_Shader_Skybox->UnBind();
	}

}