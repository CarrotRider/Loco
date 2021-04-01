#pragma once
#include "Core.h"
#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"

namespace Loco {

	class VertexArray;
	class Renderer;

	class LOCO_API Mesh
	{
	public:

		struct Vertex
		{
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TexCoords;
		};

		Mesh(Renderer* renderer, std::vector<Vertex> vertices, std::vector<unsigned> indices,
			std::vector<std::string> texturesKeys);
		~Mesh();
		void Draw(Shader* shader);

		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::vector<std::string> m_TextureKeys;
	private:
		VertexArray* m_VAO;
		Renderer* m_Renderer;
	};

}



