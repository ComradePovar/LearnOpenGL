#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "model.h"
#include "texture.h"
#include "camera.h"

/*
	callbacks
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

/*
	Initialization
*/
void glfwInitialization();
GLFWwindow* createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
int glewInitialization();
void sceneInitialization(GLFWwindow* window, GLFWkeyfun keyFun, GLFWcursorposfun cursorPosFun, GLFWscrollfun scrollFun, int& width, int& height);

void do_movement(GLfloat deltaTime);

bool keys[1024];
bool firstMove = true;
double lastX = 0, lastY = 0;
Camera camera;

const GLint N = 108;
const GLint VERTICES_COUNT = 36;
const GLfloat verticesData[N] = {
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
};

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
	sceneInitialization(window, key_callback, mouse_callback, scroll_callback, width, height);
	const GLfloat ar[2] { 0.5f, 0.2f };
	Model* cube;
	Model* lightSource;
	Shader* shader;
	Shader* lightSourceShader;
	Texture* texture1;
	Texture* texture2;
	Texture* texture3;
	try {
		shader = new Shader("Shaders/shader.vert", "Shaders/shader.frag");
		lightSourceShader = new Shader("Shaders/lightSourceShader.vert", "Shaders/lightSourceShader.frag");
		cube = new Model(vertices, N, VERTICES_COUNT);
		lightSource = new Model(vertices, N, VERTICES_COUNT);
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

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	glm::vec3 objectColor(1.0f, 0.5f, 0.31f);
	glm::vec3 lightPosition(1.2f, 1.0f, 2.0f);
	while (glfwWindowShouldClose(window) != GL_TRUE) {
		GLdouble currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		do_movement(deltaTime);

		shader->use();
		cube->bindVAO();

		glm::mat4 projectionMatrix;
		projectionMatrix = glm::perspective(glm::radians(camera.zoom), (float)width / height, 0.1f, 100.0f);
		glm::mat4 viewMatrix = camera.getViewMatrix();
		glm::mat4 modelMatrix;
		shader->sendMatrix4("model", modelMatrix);
		shader->sendMatrix4("view", viewMatrix);
		shader->sendMatrix4("projection", projectionMatrix);
		shader->sendVector3("lightColor", lightColor);
		shader->sendVector3("objectColor", objectColor);
		glDrawArrays(GL_TRIANGLES, 0, cube->getVerticesCount());

		lightSource->bindVAO();
		lightSourceShader->use();

		modelMatrix = glm::mat4();
		modelMatrix = glm::translate(modelMatrix, lightPosition);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		lightSourceShader->sendMatrix4("model", modelMatrix);
		lightSourceShader->sendMatrix4("view", viewMatrix);
		lightSourceShader->sendMatrix4("projection", projectionMatrix);
		
		glDrawArrays(GL_TRIANGLES, 0, lightSource->getVerticesCount());

		lightSource->unbindVAO();
		lightSourceShader->stop();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int keycode, int scancode, int action, int mode) {
	if (keycode == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (keycode >= 0 && keycode <= 1024) {
		if (action == GLFW_PRESS) {
			keys[keycode] = true;
		}
		else if (action == GLFW_RELEASE) {
			keys[keycode] = false;
		}
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMove) {
		lastX = xpos;
		lastY = ypos;
		firstMove = false;
	}

	GLfloat xoffset = static_cast<float>(xpos - lastX);
	GLfloat yoffset = static_cast<float>(lastY - ypos);
	lastX = xpos;
	lastY = ypos;

	camera.processMouseInput(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.processScrollInput(yoffset);
}

void do_movement(GLfloat deltaTime) {
	if (keys[GLFW_KEY_W]) {
		camera.processKeyboardInput(FORWARD, deltaTime);
	}
	if (keys[GLFW_KEY_S]) {
		camera.processKeyboardInput(BACKWARD, deltaTime);
	}
	if (keys[GLFW_KEY_A]) {
		camera.processKeyboardInput(LEFT, deltaTime);
	}
	if (keys[GLFW_KEY_D]) {
		camera.processKeyboardInput(RIGHT, deltaTime);
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
	GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return window;
}

int glewInitialization()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		return -2;
	}
	return 0;
}

void sceneInitialization(GLFWwindow* window, GLFWkeyfun keyFun, GLFWcursorposfun cursorPosFun, GLFWscrollfun scrollFun, int& width, int& height)
{
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	//glClearColor(0.2f, 0.3f, 0.4f, 0.5f);
	glClearColor(0.0f, 0.25f, 0.0f, 1.0f);

	glfwSetKeyCallback(window, keyFun);
	glfwSetCursorPosCallback(window, cursorPosFun);
	glfwSetScrollCallback(window, scrollFun);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
