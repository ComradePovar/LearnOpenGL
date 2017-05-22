#include "camera.h"

Camera::Camera() : front(glm::vec3(0.0f, 0.0f, 1.0f)), movementSpeed(SPEED),
				   sensitivity(SENSITIVITY), zoom(ZOOM), pitch(PITCH), yaw(YAW) {
	this->position = glm::vec3(0.0f, 0.0f, 3.0f);
	this->upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	updateCameraVectors();
}

Camera::Camera(glm::vec3 position, glm::vec3 upVector, GLfloat pitch, GLfloat yaw)
	: front(glm::vec3(0.0f, 0.0f, 1.0f)), movementSpeed(SPEED), sensitivity(SENSITIVITY), zoom(ZOOM) {
	this->position = position;
	this->upVector = upVector;
	this->pitch = pitch;
	this->yaw = yaw;
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(position, position + front, upVector);
}

void Camera::processMouseInput(GLfloat xoffset, GLfloat yoffset) {
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	pitch += yoffset;
	yaw += xoffset;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::processKeyboardInput(CameraMovement direction, GLfloat deltaTime) {
	GLfloat velocity = this->movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
}

void Camera::processScrollInput(GLfloat yoffset)
{
	if (zoom >= 1.0f && zoom <= 45.0f)
		zoom -= yoffset;
	if (zoom <= 1.0f)
		zoom = 1.0f;
	if (zoom >= 45.0f)
		zoom = 45.0f;
}

void Camera::updateCameraVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(front);

	this->right = glm::normalize(glm::cross(this->front, upVector));
}