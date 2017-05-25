#ifndef MODEL_H
#define MODEL_H
#define GLEW_STATIC
#include <GL\glew.h>

class Model {
private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLsizei verticesCount;
	GLsizei indicesCount;
public:
	Model(const GLfloat* verticesData, const GLint n);
	void bindVAO() const;
	void unbindVAO() const;
	GLsizei getVerticesCount() const;
	GLsizei getIndicesCount() const;
};

#endif