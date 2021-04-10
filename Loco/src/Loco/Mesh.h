#pragma once
#include "Core.h"
#include <glm/glm.hpp>

namespace Loco {

	class VertexArray;
	class Renderer;
	class Shader;
	class Material;

	class LOCO_API Mesh
	{
	public:

		struct Vertex
		{
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TexCoords;
		};

		Mesh(Renderer* renderer, 
			const std::vector<Vertex>& vertices, 
			const std::vector<unsigned>& indices,
			const std::shared_ptr<Material>& material);
		~Mesh();
		void Draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);

		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		//std::vector<std::string> m_TextureKeys;
		std::shared_ptr<Material> m_Material;
	private:
		VertexArray* m_VAO;
		Renderer* m_Renderer;
	};

}



