#include "Cube.h"



Cube::Cube(const std::string & shaderName)
{
	std::vector<Vertex> vertices = {
		//Front
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)),
		//Back
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)),
		//Top
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
		//Bottom
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f,  0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f,  0.0f)),
		//Left
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f)),
		//Right
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f,  0.0f,  0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f,  0.0f,  0.0f)),
	};

	std::vector<GLuint> indices = {
		//Front
		0, 3, 2,
		0, 2, 1,
		//Back
		5, 6, 7,
		5, 7, 4,
		//Top
		10, 11, 9,
		10, 9, 8,
		//Bottom
		12, 13, 15,
		12, 15, 14,
		//Left
		16, 19, 18,
		16, 18, 17,
		//Right
		23, 20, 21,
		23, 21, 22,
	};

	m_shader.Initialize("./res/" + shaderName);
	m_mesh.Initialize(vertices, indices);
}


Cube::~Cube()
{
}
