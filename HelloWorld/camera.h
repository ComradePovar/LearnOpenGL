#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera {
private:
	void updateCameraVectors();
public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 upVector;

	GLfloat pitch;
	GLfloat yaw;

	GLfloat movementSpeed;
	GLfloat sensitivity;
	GLfloat zoom;

	Camera();
	Camera(glm::vec3 position, glm::vec3 upVector, GLfloat pitch, GLfloat yaw);


	glm::mat4 getViewMatrix() const;

	void processMouseInput(GLfloat xoffset, GLfloat yoffset);
	void processKeyboardInput(CameraMovement direction, GLfloat deltaTime);
	void processScrollInput(GLfloat yoffset);
};