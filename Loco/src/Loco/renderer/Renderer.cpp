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

		// Pass Final
		m_ScreenVA = new VertexArray(m_ScreenPanel, 6, m_Indices_Screen, 6,
			BufferLayout::POS_TEX);
		initDeferredShading();
		// Init Scene
		initAxis();
		initSkybox();

		// Init Custom
		m_ShaderDefault = GetShader("default.vs", "default.fs");
	}

	void Renderer::ShutDown()
	{
		delete m_ScreenVA;

		glfwTerminate();
	}

	void Renderer::Draw(float deltaTime)
	{
		// Pass One
		m_GBuffer->Bind();

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//drawSkybox();
		//drawAxis();

		// 绘制场景
		for (auto& renderableComp : m_RenderebleComps)
		{
			renderableComp->Draw();
		}

		m_GBuffer->UnBind();

		// Lighting Pass
		glViewport(0, 0, m_Width, m_Height);
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_ShaderLightingPass->Bind();	
		m_ShaderLightingPass->SetUniform("gPosition", 0);
		m_ShaderLightingPass->SetUniform("gNormal", 1);
		m_ShaderLightingPass->SetUniform("gAlbedoSpec", 2);
		m_PosTexture->Active(0);
		m_NormTexture->Active(1);
		m_ColorTexture->Active(2);
		setLightingUniforms(m_ShaderLightingPass);
		m_ScreenVA->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		m_ScreenVA->UnBind();
		m_PosTexture->UnBind();
		m_NormTexture->UnBind();
		m_ColorTexture->UnBind();
		m_ShaderLightingPass->UnBind();

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
			std::move(std::make_unique<Model>(this, fileName))));
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

		m_VAO_Axis->Bind();

		m_Shader_Axis->SetUniform("color", glm::vec3(1.0f, 0.0f, 0.0f));
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
		m_Shader_Axis->SetUniform("color", glm::vec3(0.0f, 1.0f, 0.0f));
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(2 * sizeof(float)));
		m_Shader_Axis->SetUniform("color", glm::vec3(0.0f, 0.0f, 1.0f));
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(4 * sizeof(float)));

		m_VAO_Axis->UnBind();

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
		m_VAO_Skybox->Bind();

		m_CubeTexture->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		m_VAO_Skybox->UnBind();
		glDepthMask(GL_TRUE);

		m_Shader_Skybox->UnBind();
	}

	void Renderer::initDeferredShading()
	{
		m_GBuffer = std::make_shared<FrameBuffer>();

		m_PosTexture = std::make_shared<Texture>();
		m_PosTexture->Image2D(nullptr, DataType::Float, Format::RGB, m_Width, m_Height, InternalFormat::RGB);
		m_PosTexture->SetFilters(Filter::Nearest, Filter::Nearest);
		m_GBuffer->BindTexture(*m_PosTexture, GL_COLOR_ATTACHMENT0);

		m_NormTexture = std::make_shared<Texture>();
		m_NormTexture->Image2D(nullptr, DataType::Float, Format::RGB, m_Width, m_Height, InternalFormat::RGB);
		m_NormTexture->SetFilters(Filter::Nearest, Filter::Nearest);
		m_GBuffer->BindTexture(*m_NormTexture, GL_COLOR_ATTACHMENT1);

		m_ColorTexture = std::make_shared<Texture>();
		m_ColorTexture->Image2D(nullptr, DataType::UnsignedByte, Format::RGBA, m_Width, m_Height, InternalFormat::RGBA);
		m_ColorTexture->SetFilters(Filter::Nearest, Filter::Nearest);
		m_GBuffer->BindTexture(*m_ColorTexture, GL_COLOR_ATTACHMENT2);
		
		unsigned attachments[3]{ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
		glDrawBuffers(3, attachments);

		m_DepthBuffer = std::make_shared<RenderBuffer>(GL_DEPTH24_STENCIL8, m_Width, m_Height);
		m_GBuffer->BindRenderBuffer(*m_DepthBuffer);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		}

		m_GBuffer->UnBind();

		m_ShaderLightingPass = GetShader("final_pass.vs", "deferred_shading.fs");
	}

	// 设置光照 Uniforms: 灯光信息，像机信息
	void Renderer::setLightingUniforms(std::shared_ptr<Shader> shader)
	{
		shader->Bind();
		// Camera Info
		shader->SetUniform("viewPos", GetGame()->GetCamera()->Position);
		// DirLights Info
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
		// PointLights Info
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
	}
}
