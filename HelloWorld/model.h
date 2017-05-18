#pragma once
class Model {
private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLsizei verticesCount;
	GLsizei indicesCount;
public:
	Model();
	void bindVAO();
	void unbindVAO();
	GLsizei getVerticesCount();
	GLsizei getIndicesCount();
};