#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GL\glew.h>

class Shader {
private:	
	GLuint shaderProgram;

	GLint createShader(GLenum shaderType, GLuint& shaderId, const GLchar* fileName);
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void use();
	void stop();
	GLuint getShaderProgramId();
};

#endif