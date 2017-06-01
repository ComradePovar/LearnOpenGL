#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <string>
#include <sstream>

#define GLEW_STATIC
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
private:	
	GLuint shaderProgram;
	GLint createShader(GLenum shaderType, GLuint& shaderId, const GLchar* fileName);
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void use() const;
	void stop() const;

	void sendMatrix4(const GLchar* uniformName, glm::mat4 matrix) const;
	void sendMatrix3(const GLchar* uniformName, glm::mat3 matrix) const;
	void sendVector3(const GLchar* uniformName, glm::vec3 vector) const;
	void sendInt(const GLchar* uniformName, const GLint value) const;
	void sendFloat(const GLchar* uniformName, const GLfloat value) const;
	GLuint getShaderProgramId() const;
};

#endif