#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
#include "shader.h"
#include "model.h"

/*
	Key callback
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

/*
	Initialization
*/
void glfwInitialization();
GLFWwindow* createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
int glewInitialization();
void sceneInitialization(GLFWwindow* window, GLFWkeyfun cbfun);

int main() {
	glfwInitialization();

	GLFWwindow* window = createWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (glewInitialization() == -2) {
		std::cout << "FAILED TO INITIALIZE GLEW\n";
		glfwTerminate();
		return -2;
	}

	sceneInitialization(window, key_callback);

	Model* model;
	Shader* shader;
	try {
		model = new Model();
		shader   = new Shader();
	}
	catch (std::exception ex) {
		std::cout << ex.what();
		glfwTerminate();
		return -3;
	}

	while (glfwWindowShouldClose(window) != GL_TRUE) {
		glClear(GL_COLOR_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glfwPollEvents();


		shader->use();
		model->bindVAO();

		glDrawElements(GL_TRIANGLES, model->getIndicesCount(), GL_UNSIGNED_INT, 0);

		shader->stop();
		model->unbindVAO();


		glfwSwapBuffers(window);
	}
	
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int keycode, int scancode, int action, int mode) {
	if (keycode == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void glfwInitialization()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

GLFWwindow* createWindow(int width, int height, const char * title, GLFWmonitor * monitor, GLFWwindow * share)
{
	return glfwCreateWindow(width, height, title, monitor, share);
}

int glewInitialization()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		return -2;
	}
	return 0;
}

void sceneInitialization(GLFWwindow* window, GLFWkeyfun cbfun)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	glClearColor(0.2f, 0.3f, 0.4f, 0.5f);

	glfwSetKeyCallback(window, cbfun);
}
