#pragma once
#include "Core.h"

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Loco
{
	class Renderer;
	class Shader;
	class Texture;

	class LOCO_API Model
	{
	public:
		Model(Renderer* renderer, const std::string& path)
			: m_Renderer(renderer)
		{
			LoadModel(path);
		}

		void Draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
	private:
		void LoadModel(const std::string& path);
		void ProcessNode(const aiNode* node, const aiScene* scene);
		Mesh* ProcessMesh(const aiMesh* mesh, const aiScene* scene);
		std::shared_ptr<Texture> LoadMaterialTextures(
			aiMaterial* mat, aiTextureType type);
	private:
		std::vector<Mesh*> m_Meshes;
		Renderer* m_Renderer;
		//std::string m_Dir;
	};
}


