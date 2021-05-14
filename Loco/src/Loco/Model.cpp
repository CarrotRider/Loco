#include "stdafx.h"
#include "Model.h"
#include "Game.h"
#include "Loco/Renderer/Renderer.h"
#include "Loco/Renderer/Shader.h"
#include "Texture.h"
#include "Loco/Mat_Default_Tex.h"
#include "Loco/Mat_Default_No_Tex.h"

#include "Path.h"


namespace Loco {

	void Model::Draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
	{
		for (auto& mesh : m_Meshes)
		{
			mesh->Draw(model, view, projection);
		}
	}

	void Model::LoadModel(const std::string& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path.c_str(), 
			aiProcess_Triangulate | aiProcess_FlipUVs);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}
		//m_Dir = path.substr(0, path.find_first_of('/'));
		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(const aiNode* node, const aiScene* scene)
	{
		// 处理节点所有的网格（如果有的话）
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.push_back(ProcessMesh(mesh, scene));
		}
		// 接下来对它的子节点重复这一过程
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh* Model::ProcessMesh(const aiMesh* mesh, const aiScene* scene)
	{
		// 获取顶点数据
		std::vector<Mesh::Vertex> vertices;
		for (unsigned i = 0; i < mesh->mNumVertices; i++)
		{
			Mesh::Vertex vertex;
			glm::vec3 pos(mesh->mVertices[i].x, 
				mesh->mVertices[i].y,
				mesh->mVertices[i].z);
			vertex.Position = pos;
			glm::vec3 norm(mesh->mNormals[i].x, 
				mesh->mNormals[i].y, 
				mesh->mNormals[i].z);
			vertex.Normal = norm;
			if (mesh->mTextureCoords[0])
			{
				glm::vec2 tex(mesh->mTextureCoords[0][i].x,
					mesh->mTextureCoords[0][i].y);
				vertex.TexCoords = tex;
			}
			else
			{
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			}
			vertices.push_back(vertex);
		}

		// 获取顶点索引
		std::vector<unsigned int> indices;
		for (unsigned i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		// 获取纹理
		std::shared_ptr<Material> mat = nullptr;
		std::shared_ptr<Shader> shader = nullptr;
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			
			
			std::shared_ptr<Texture> diffuse = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
			std::shared_ptr<Texture> specular = LoadMaterialTextures(material, aiTextureType_SPECULAR);
			std::shared_ptr<Texture> normal = LoadMaterialTextures(material, aiTextureType_NORMALS);

			shader = m_Renderer->GetShader("default.vs", "default_no_normal_gbuffer.fs");

			float shininess;
			material->Get(AI_MATKEY_SHININESS, shininess);
			mat = std::make_shared<Mat_Default_Tex>(shader, diffuse, specular, normal, shininess);
			aiString name;
			material->Get(AI_MATKEY_NAME, name);
			std::string key = m_Dir + name.C_Str();
			m_Renderer->AddMaterial(mat, key);
			return new Mesh(m_Renderer, vertices, indices, m_Renderer->GetMaterial(key));
		}
		else
		{
			glm::vec3 defaultDiffuseColor{ 1.0f, 1.0f, 1.0f };
			shader = m_Renderer->GetShader("default.vs", "default_no_normal_gbuffer.fs");
			mat = std::make_shared<Mat_Default_Tex>(shader, defaultDiffuseColor);
			m_Renderer->AddMaterial(mat, m_Dir);
			return new Mesh(m_Renderer, vertices, indices, m_Renderer->GetMaterial(m_Dir));
		}
		
	}

	std::shared_ptr<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type)
	{
		Texture::Type typeLoco = Texture::Type::NONE;
		
		switch (type)
		{
		case aiTextureType_NONE:
			break;
		case aiTextureType_DIFFUSE:
			typeLoco = Texture::Type::DIFFUSE;
			break;
		case aiTextureType_SPECULAR:
			typeLoco = Texture::Type::SPECULAR;
			break;
		//case aiTextureType_AMBIENT:
		//	break;
		//case aiTextureType_EMISSIVE:
		//	break;
		//case aiTextureType_HEIGHT:
		//	break;
		case aiTextureType_NORMALS:
			typeLoco = Texture::Type::NORMAL;
			break;
		//case aiTextureType_SHININESS:
		//	break;
		//case aiTextureType_OPACITY:
		//	break;
		//case aiTextureType_DISPLACEMENT:
		//	break;
		//case aiTextureType_LIGHTMAP:
		//	break;
		//case aiTextureType_REFLECTION:
		//	break;
		//case aiTextureType_BASE_COLOR:
		//	break;
		//case aiTextureType_NORMAL_CAMERA:
		//	break;
		//case aiTextureType_EMISSION_COLOR:
		//	break;
		//case aiTextureType_METALNESS:
		//	break;
		//case aiTextureType_DIFFUSE_ROUGHNESS:
		//	break;
		//case aiTextureType_AMBIENT_OCCLUSION:
		//	break;
		//case aiTextureType_UNKNOWN:
		//	break;
		//case _aiTextureType_Force32Bit:
		//	break;
		default:
			break;
		}

//		for (unsigned i = 0; i < mat->GetTextureCount(type); i++)
//		{
			aiString str;
			mat->GetTexture(type, 0, &str);
			std::string path =/* MODEL_PATH + */std::string(str.C_Str());
			m_Renderer->LoadTexture(path, typeLoco);
			std::shared_ptr<Texture> texture = std::shared_ptr<Texture>(m_Renderer->GetTexture(path));
//		}
		return texture;
	}
}