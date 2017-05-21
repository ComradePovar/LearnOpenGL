#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "model.h"
#include "texture.h"

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
void sceneInitialization(GLFWwindow* window, GLFWkeyfun cbfun, int& width, int& height);

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

	int width, height;
	sceneInitialization(window, key_callback, width, height);

	Model* model;
	Shader* shader;
	Texture* texture1;
	Texture* texture2;
	Texture* texture3;
	try {
		shader = new Shader("Shaders/shader.vert", "Shaders/shader.frag");
		model  = new Model();
		texture1 = new Texture("Textures/container.jpg");
		texture2 = new Texture("Textures/awesomeface.png");
		texture3 = new Texture("Textures/epifan.jpg");
	}
	catch (std::exception ex) {
		std::cout << ex.what();
		glfwTerminate();
		return -3;
	}
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	while (glfwWindowShouldClose(window) != GL_TRUE) {
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glfwPollEvents();


		shader->use();
		model->bindVAO();

		glm::mat4 viewMatrix;
		viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 projectionMatrix;
		projectionMatrix = glm::perspective(45.0f, (float)width / height, 0.1f, 100.0f);
		shader->sendViewMatrix(viewMatrix);
		shader->sendProjectionMatrix(projectionMatrix);
		shader->sendSampler(texture1->getTextureId(), texture1->getTextureUnit());
		shader->sendSampler(texture2->getTextureId(), texture2->getTextureUnit());
		shader->sendSampler(texture3->getTextureId(), texture3->getTextureUnit());

		for (int i = 0; i < 10; i++) {
			glm::mat4 modelMatrix;
			modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
			GLfloat angle = i % 3 == 0 ? glm::radians(20.0f * i) : glm::radians(static_cast<float>(glfwGetTime())*30);
			modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(1.0f, 0.3f, 0.5f));

			shader->sendModelMatrix(modelMatrix);
			//glDrawElements(GL_TRIANGLES, model->getIndicesCount(), GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, model->getVerticesCount());
		}

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

void sceneInitialization(GLFWwindow* window, GLFWkeyfun cbfun, int& width, int& height)
{
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	//glClearColor(0.2f, 0.3f, 0.4f, 0.5f);
	glClearColor(0.0f, 0.25f, 0.0f, 1.0f);

	glfwSetKeyCallback(window, cbfun);
}
