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
void initModelShader(const Shader* shader, Texture** textures);

void do_movement(GLfloat deltaTime);

bool keys[1024];
bool firstMove = true;
double lastX = 0, lastY = 0;
Camera camera;

const GLint N = 288;
const GLint VERTICES_COUNT = 36;
const GLfloat verticesData[N] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 lightPosition(1.2f, 1.0f, 2.0f);
float angleLightPosition;


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
	Texture* containerTexture;
	Texture* containerTextureSpecular;
	Texture** textures = new Texture*[2];
	try {
		shader = new Shader("Shaders/shader.vert", "Shaders/shader.frag");
		lightSourceShader = new Shader("Shaders/lightSourceShader.vert", "Shaders/lightSourceShader.frag");
		cube = new Model(verticesData, N);
		lightSource = new Model(verticesData, N);
		containerTexture = new Texture("Textures/container2.png");
		containerTextureSpecular = new Texture("Textures/container2_specular.png");

		textures[0] = containerTexture;
		textures[1] = containerTextureSpecular;
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

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;


	initModelShader(shader, textures);
	while (glfwWindowShouldClose(window) != GL_TRUE) {
		GLdouble currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		do_movement(deltaTime);

		lightSourceShader->use();
		lightSource->bindVAO();

		glm::mat4 projectionMatrix;
		projectionMatrix = glm::perspective(glm::radians(camera.zoom), (float)width / height, 0.1f, 100.0f);
		glm::mat4 viewMatrix = camera.getViewMatrix();
		glm::mat4 modelMatrix;
		glm::mat3 normalMatrix;

		lightSourceShader->sendMatrix4("view", viewMatrix);
		lightSourceShader->sendMatrix4("projection", projectionMatrix);

		modelMatrix = glm::mat4();
		modelMatrix = glm::rotate(modelMatrix, glm::radians(angleLightPosition), glm::vec3(-1.0f, 0.0f, 1.0f));
		modelMatrix = glm::translate(modelMatrix, lightPosition);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		lightSourceShader->sendMatrix4("model", modelMatrix);

		glDrawArrays(GL_TRIANGLES, 0, lightSource->getVerticesCount());


		glm::vec3 lightPositionCurrent = glm::vec3(modelMatrix * glm::vec4(lightPosition, 1.0f));
		shader->use();
		cube->bindVAO();

		shader->sendMatrix3("normalMatrix", normalMatrix);
		shader->sendVector3("viewPos", camera.position);
		shader->sendVector3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		shader->sendVector3("pointLights[0].position", lightPositionCurrent);
		shader->sendVector3("spotlight.position", camera.position);
		shader->sendVector3("spotlight.direction", camera.front);
		shader->sendMatrix4("model", modelMatrix);
		shader->sendMatrix4("view", viewMatrix);
		shader->sendMatrix4("projection", projectionMatrix);

		for (int i = 0; i < 10; i++) {
			glm::mat4 modelMatrix, normalMatrix;
			modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
			float angle = 20 * i;
			modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			normalMatrix = glm::transpose(glm::inverse(modelMatrix));
			shader->sendMatrix4("model", modelMatrix);
			shader->sendMatrix4("normalMatrix", normalMatrix);


			normalMatrix = glm::transpose(glm::inverse(modelMatrix));
			glDrawArrays(GL_TRIANGLES, 0, cube->getVerticesCount());
		}

		cube->unbindVAO();
		shader->stop();

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
	float rotationSpeed = 40.0f * deltaTime;
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
	if (keys[GLFW_KEY_UP]) {
		angleLightPosition += rotationSpeed;
	}
	if (keys[GLFW_KEY_DOWN]) {
		angleLightPosition -= rotationSpeed;
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

void initModelShader(const Shader* shader, Texture** textures) {
	shader->use();
	shader->sendFloat("material.shininess", 64.0f);
	textures[0]->bindTexture();
	shader->sendInt("material.diffuse", textures[0]->getTextureUnit());
	textures[1]->bindTexture();
	shader->sendInt("material.specular", textures[1]->getTextureUnit());
	shader->sendVector3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

	shader->sendVector3("dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader->sendVector3("dirLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	shader->sendVector3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	shader->sendVector3("pointLights[0].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader->sendVector3("pointLights[0].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	shader->sendVector3("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->sendFloat("pointLights[0].constant", 1.0f);
	shader->sendFloat("pointLights[0].linear", 0.09f);
	shader->sendFloat("pointLights[0].quadratic", 0.032f);

	shader->sendFloat("spotlight.cutOff", glm::cos(glm::radians(12.5f)));
	shader->sendVector3("spotlight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader->sendVector3("spotlight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	shader->sendVector3("spotlight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->stop();
}