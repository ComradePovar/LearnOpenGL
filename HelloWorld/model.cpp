#include <GL\glew.h>
#include "model.h"

Model::Model() {
	GLfloat vertices[] = {
		0.5f,  0.5f, 0.0f,
	    0.5f, -0.5f, 0.0f,
	   -0.5f, -0.5f, 0.0f,
	   -0.5f,  0.5f, 0.0f
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	verticesCount = sizeof(vertices) / sizeof(vertices[0]);
	indicesCount = sizeof(indices) / sizeof(indices[0]);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glBindVertexArray(0);
}

void Model::bindVAO() {
	glBindVertexArray(VAO);
}

void Model::unbindVAO() {
	glBindVertexArray(0);
}

GLsizei Model::getVerticesCount() {
	return verticesCount;
}

GLsizei Model::getIndicesCount() {
	return indicesCount;
}