#include "Camera.h"

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%  StaticInitialize  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

extern const unsigned int windowWidth, windowHeight;
extern float deltaTime;
extern float lastFrame;

Camera Input::camera;
std::pair<float, float> Input::lastMousePosition(windowWidth / 2.0, windowHeight / 2.0);
bool Input::firstMouse = false;



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  CameraClass  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#pragma region CameraClass

// ----------------------PUBLIC-----------------------------

Camera::Camera(const glm::vec3& position, const glm::vec3& up, const float yaw, const float pitch)
	: positionVec(position), worldUpVec(up), frontVec(glm::vec3(0.0f, 0.0f, -1.0f)), 
	yaw(yaw), pitch(pitch), fov(FOV), moveSpeed(SPEED), rotateSensitivity(SENSITIVITY)
{
	updateCameraVectors();
}

float Camera::getFOV() const
{
	return fov;
}

void Camera::processMouseMovement(const std::pair<float, float> offset, const GLboolean constrainPitch)
{
	yaw = yaw + offset.first;
	pitch = pitch + offset.second;
	if (constrainPitch) {
		if (pitch > 89.0f) pitch = 89.0f;
		if (pitch < -89.0f) pitch = -89.0f;
	}
	updateCameraVectors();
}

void Camera::processKeyMovement(const CameraMovement direction, const float deltaTime)
{
	float velocity = moveSpeed * deltaTime;
	if (direction == FORWARD) positionVec = positionVec + frontVec * velocity;
	if (direction == BACKWARD) positionVec = positionVec - frontVec * velocity;
	if (direction == LEFT) positionVec = positionVec - rightVec * velocity;
	if (direction == RIGHT) positionVec = positionVec + rightVec * velocity;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(positionVec, positionVec + frontVec, upVec);
}


// ----------------------PRIVATE-----------------------------

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	front.y = std::sin(glm::radians(pitch));
	front.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	frontVec = glm::normalize(front);
	rightVec = glm::normalize(glm::cross(frontVec, worldUpVec));
	upVec = glm::normalize(glm::cross(rightVec, frontVec));
}

#pragma endregion



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% InputClass  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#pragma region InputClass

// ----------------------PUBLIC-----------------------------

Input::Input(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Camera& Input::getCamera() const
{
	return camera;
}

void Input::pressKeyboard(GLFWwindow* window)
{
	pressEscape(window);
	pressDirection(window);
}

void Input::pressEscape(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

void Input::pressDirection(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.processKeyMovement(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.processKeyMovement(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.processKeyMovement(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.processKeyMovement(RIGHT, deltaTime);
}

void Input::activateCallback(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);
}

void Input::mouseCallback(GLFWwindow* window, double xPosition, double yPosition)
{
	if (firstMouse) {
		lastMousePosition = { xPosition, yPosition };
		firstMouse = false;
	}
	float xOffset = xPosition - lastMousePosition.first;
	float yOffset = lastMousePosition.second - yPosition;
	lastMousePosition = { xPosition, yPosition };
	camera.processMouseMovement(std::make_pair(xOffset, yOffset));
}

void Input::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	if (camera.fov >= 1.0f && camera.fov <= 45.0f) camera.fov = camera.fov - yOffset;
	if (camera.fov <= 1.0f) camera.fov = 1.0f;
	if (camera.fov >= 45.0f) camera.fov = 45.0f;
}

void Input::frameBufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}

// ----------------------PRIVATE-----------------------------

#pragma endregion

