#include "stdafx.h"
#include "Model.h"
#define RES_ROOT "./assets/models/"


namespace Loco {

	void Model::Draw(Shader* shader)
	{
		for (auto& mesh : m_Meshes)
		{
			mesh.Draw(shader);
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

	Mesh Model::ProcessMesh(const aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Mesh::Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture*> textures;

		// 获取顶点数据
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
		for (unsigned i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		// 获取纹理
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<Texture*> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
			std::vector<Texture*> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}
		return Mesh(vertices, indices, textures);
	}

	std::vector<Texture*> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type)
	{
		std::vector<Texture*> textures;
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
		//case aiTextureType_NORMALS:
		//	break;
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
		//if (typeLoco != Texture::Type::NONE)
		//{
			for (unsigned i = 0; i < mat->GetTextureCount(type); i++)
			{
				aiString str;
				mat->GetTexture(type, i, &str);
				std::string s = RES_ROOT + std::string(str.C_Str());
				//std::cout << s <<" " << (int)typeLoco << std::endl;
				Texture* texture = new Texture(s, typeLoco);
				textures.push_back(texture);
			}
		//}
		return textures;
	}
}