#include "shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
	GLuint vertexShader, fragmentShader;
	if (!createShader(GL_VERTEX_SHADER, vertexShader, vertexPath)) {
		GLchar infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		throw std::exception(infoLog);
	}
	if (!createShader(GL_FRAGMENT_SHADER, fragmentShader, fragmentPath)) {
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

GLint Shader::createShader(GLenum shaderType, GLuint& shaderId, const GLchar* fileName) {
	std::string shaderSource;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	shaderFile.open(fileName);

	std::stringstream shaderStream;
	shaderStream << shaderFile.rdbuf();
	shaderSource = shaderStream.str();

	shaderFile.close();
	const GLchar* shaderCode = shaderSource.c_str();

	shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &shaderCode, nullptr);
	glCompileShader(shaderId);

	GLint compileStatus;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
	
	return compileStatus;
}

void Shader::use() const {
	glUseProgram(shaderProgram);
}

void Shader::stop() const {
	glUseProgram(0);
}

GLuint Shader::getShaderProgramId() const {
	return shaderProgram;
}

void Shader::sendTransformationMatrix(const glm::mat4 matrix) const {
	GLint transformationMatrixLoc = glGetUniformLocation(shaderProgram, "transformationMatrix");
	glUniformMatrix4fv(transformationMatrixLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::sendSampler(GLuint textureId, GLuint textureUnit) const {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureId);
	GLchar samplerName[12];
	snprintf(samplerName, sizeof(samplerName), "%s%d", "ourTexture", textureUnit);
	glUniform1i(glGetUniformLocation(shaderProgram, samplerName), textureUnit);
}