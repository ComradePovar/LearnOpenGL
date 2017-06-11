#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <assimp\postprocess.h>
#include <vector>
#include "shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Texture {
	GLuint id;
	std::string type;
	aiString path;
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	void draw(Shader shader);
private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	void setupMesh();
};