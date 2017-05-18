#include <iostream>
#include <GL\glew.h>
#include "shader.h"

Shader::Shader() {
	GLuint vertexShader, fragmentShader;
	if (!createShader(GL_VERTEX_SHADER, vertexShader)) {
		GLchar infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		throw std::exception(infoLog);
	}
	if (!createShader(GL_FRAGMENT_SHADER, fragmentShader)) {
		GLchar infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		throw std::exception(infoLog);
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	GLint isSuccess;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isSuccess);
	if (!isSuccess) {
		GLchar infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		throw std::exception(infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLint Shader::createShader(GLenum shaderType, GLuint& shaderId) {

	shaderId = glCreateShader(shaderType);
	switch (shaderType) {
		case GL_VERTEX_SHADER:
			glShaderSource(shaderId, 1, &vertexShaderSource, nullptr);
			break;
		case GL_FRAGMENT_SHADER:
			glShaderSource(shaderId, 1, &fragmentShaderSource, nullptr);
			break;
		default:
			return -1;
	}
	glCompileShader(shaderId);

	GLint compileStatus;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
	
	return compileStatus;
}

void Shader::use() {
	glUseProgram(shaderProgram);
}

void Shader::stop() {
	glUseProgram(0);
}