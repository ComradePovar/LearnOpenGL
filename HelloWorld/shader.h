#pragma once
class Shader {
private:	
	GLuint shaderProgram;

	const GLchar* vertexShaderSource = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position, 1.0);\n"
		"}\0";
	const GLchar* fragmentShaderSource = 
		"#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}";

	GLint createShader(GLenum shaderType, GLuint& shaderId);
public:
	Shader();
	void use();
	void stop();
};