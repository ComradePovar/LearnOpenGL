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

	void sendTransformationMatrix(const glm::mat4 matrix) const;
	void sendSampler(GLuint textureId, GLuint textureUnit) const;
	GLuint getShaderProgramId() const;
};

#endif