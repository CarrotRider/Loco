#include "stdafx.h"
#include "Loco/Renderer/Renderer.h"
#include "Loco/Renderer/Shader.h"
#include "Loco/Renderer/FrameBuffer.h"
#include "Loco/Renderer/RenderBuffer.h"
#include "Loco/Components/RenderableComponent.h"
#include "Loco/Components/DirLightComponent.h"
#include "Loco/Components/PointLightComponent.h"
#include "Loco/Camera.h"
#include "Loco/Game.h"
#include "Loco/CubeTexture.h"
#include "VertexArray.h"
#include "Loco/Model.h"
#include "Loco/Material.h"


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

		//initShadow();

		// Init Frame Buffer
		m_FrameBuffer = new FrameBuffer();

		m_ScreenTexture = new Texture(m_Width, m_Height, Texture::Type::NONE);
		m_FrameBuffer->BindTexture(*m_ScreenTexture, GL_COLOR_ATTACHMENT0);
		
		m_ShadowTexture = std::make_shared<Texture>(m_ShadowWidth, m_ShadowHeight, Texture::Type::SHADOW);
		m_FrameBuffer->BindTexture(*m_ShadowTexture, GL_DEPTH_ATTACHMENT);
		//m_RenderBuffer = new RenderBuffer(GL_DEPTH24_STENCIL8, m_Width, m_Height);
		//m_FrameBuffer->BindRenderBuffer(*m_RenderBuffer);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		}
		m_FrameBuffer->UnBind();

		// Pass Final
		m_ScreenVA = new VertexArray(m_ScreenPanel, 6, m_Indices_Screen, 6, 
			BufferLayout::POS_TEX);
		m_ShaderFinal = GetShader("final_pass.vs", "final_pass.fs");
		// Init Scene
		initAxis();
		initSkybox();

		// Init Custom
		m_ShaderDefault = GetShader("default.vs", "default.fs");
	}

	void Renderer::ShutDown()
	{	
		delete m_ScreenVA;
		delete m_FrameBuffer;
		delete m_ScreenTexture;
		delete m_RenderBuffer;

		glfwTerminate();
	}

	void Renderer::Draw(float deltaTime)
	{
		// Pass One
		m_FrameBuffer->Bind();
		
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//drawSkybox();
		drawAxis();
		
		// 对场景内所有的 shader 设置光照
		for (auto& item : m_Materials)
		{
			Shader* shader = item.second->GetShader();
			shader->Bind();

			shader->SetUniform("viewPos", GetGame()->GetCamera()->Position);
			// Set DirLights
			int len = m_DirLights.size();
			std::string s0 = "dirLights[";
			std::string s1 = "].Direction";
			std::string s2 = "].Color";
			for (int i = 0; i < len; i++)
			{
				std::string idx = std::to_string(i);
				shader->SetUniform(s0 + idx + s1, m_DirLights[i]->GetDirection());
				shader->SetUniform(s0 + idx + s2, m_DirLights[i]->GetColor());
			}
			// Set PointLights
			len = m_PointLights.size();
			s0 = "pointLights[";
			s1 = "].Position";
			s2 = "].Color";
			std::string s3 = "].Radius";
			std::string s4 = "].Kc";
			std::string s5 = "].Kl";
			std::string s6 = "].Kq";
			for (int i = 0; i < len; i++)
			{
				std::string idx = std::to_string(i);
				shader->SetUniform(s0 + idx + s1, m_PointLights[i]->GetPosition());
				shader->SetUniform(s0 + idx + s2, m_PointLights[i]->GetColor());
				shader->SetUniform(s0 + idx + s3, m_PointLights[i]->GetRadius());
				shader->SetUniform(s0 + idx + s4, m_PointLights[i]->GetAttenConst());
				shader->SetUniform(s0 + idx + s5, m_PointLights[i]->GetAttenLinear());
				shader->SetUniform(s0 + idx + s6, m_PointLights[i]->GetAttenQuad());
			}
			shader->UnBind();
		}

		//glViewport(0, 0, m_ShadowWidth, m_ShadowHeight);
		//m_ShadowBuffer->Bind();
		//glClear(GL_DEPTH_BUFFER_BIT);
		// todo: 配置 shader 矩阵
		// todo: 渲染场景
		// 绘制场景
		for (auto& renderableComp : m_RenderebleComps)
		{
			renderableComp->Draw();
		}
		//m_ShadowBuffer->UnBind();

		m_FrameBuffer->UnBind();
		
		// Pass Final
		
		glViewport(0, 0, m_Width, m_Height);
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);

		m_ShaderFinal->Bind();
		m_ScreenVA->SetActive(true);
		m_ScreenTexture->Active(0);
		//m_ShadowTexture->Active(0);
		//m_ShadowCTexture->Active(0);
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

	void Renderer::LoadShader(const std::string& vs, const std::string& fs)
	{
		std::string key = vs + fs;
		m_Shaders.insert(std::pair<std::string, std::shared_ptr<Shader>>(
			key, std::move(std::make_shared<Shader>(vs, fs))));
	}

	std::shared_ptr<Shader> Renderer::GetShader(const std::string& vs, const std::string& fs)
	{
		std::string key = vs + fs;
		auto iter = m_Shaders.find(key);
		if (iter == m_Shaders.end())
		{
			LoadShader(vs, fs);
		}
		iter = m_Shaders.find(key);
		return iter == m_Shaders.end() ? nullptr : (*iter).second;
	}

	void Renderer::AddMaterial(const std::shared_ptr<Material>& material, const std::string& name)
	{
		m_Materials.insert(std::pair<std::string, std::shared_ptr<Material>>(name, material));
	}

	std::shared_ptr<Material> Renderer::GetMaterial(const std::string& name)
	{
		auto iter = m_Materials.find(name);
		return iter == m_Materials.end() ? nullptr : (*iter).second;
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

	void Renderer::AddLightComp(DirLightComponent* dirLight)
	{
		m_DirLights.push_back(dirLight);
	}

	void Renderer::AddLightComp(PointLightComponent* pointLight)
	{
		m_PointLights.push_back(pointLight);
	}

	void Renderer::RemoveLightComp(DirLightComponent* dirLight)
	{
		auto iter = std::find(m_DirLights.begin(), m_DirLights.end(), dirLight);
		if (iter != m_DirLights.end())
		{
			m_DirLights.erase(iter);
		}
	}

	void Renderer::RemoveLightComp(PointLightComponent* pointLight)
	{
		auto iter = std::find(m_PointLights.begin(), m_PointLights.end(), pointLight);
		if (iter != m_PointLights.end())
		{
			m_PointLights.erase(iter);
		}
	}

	void Renderer::initAxis()
	{
		m_VAO_Axis = std::make_unique<VertexArray>((float*)m_Vecs_Axis, 6,
			m_Indices_Axis, 6, BufferLayout::POS);
		m_Shader_Axis = GetShader("axis.vs", "axis.fs");
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
		m_Shader_Skybox = GetShader("sky_box.vs", "sky_box.fs");
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

	void Renderer::initShadow()
	{
		m_ShadowBuffer = std::make_shared<FrameBuffer>();
		m_ShadowTexture = std::make_shared<Texture>(
			m_ShadowWidth, m_ShadowHeight, Texture::Type::SHADOW);
		m_ShadowCTexture = std::make_shared<Texture>(
			m_ShadowWidth, m_ShadowHeight, Texture::Type::NONE);
		m_ShadowBuffer->Bind();
		//m_ShadowBuffer->BindTexture(*m_ShadowCTexture);
		m_ShadowBuffer->BindTexture(*m_ShadowTexture, GL_DEPTH_ATTACHMENT);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		}
		m_ShadowBuffer->UnBind();
		m_ShadowShader = std::make_shared<Shader>(
			"simple_depth_shader.vs", "simple_depth_shader.fs");

	}

}
