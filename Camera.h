#pragma once
#include <utility>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  CameraClass  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// ~~~~~~~~~~~~~CONSTANT & ENUMERATION~~~~~~~~~~~~~~~~

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
const float FOV = 45.0f;

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Camera
{
public:
    friend class Input;
	Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), const float yaw = YAW, const float pitch = PITCH);
	~Camera() = default;

    float getFOV() const;
    void processMouseMovement(const std::pair<float, float> offset, const GLboolean constrainPitch = true);
    void processKeyMovement(const CameraMovement direction, const float deltaTime);
    glm::mat4 getViewMatrix() const;

private:
    float pitch;
    float yaw;
    float fov;
    float moveSpeed;
    float rotateSensitivity;
    glm::vec3 positionVec;
    glm::vec3 frontVec;
    glm::vec3 upVec;
    glm::vec3 rightVec;
    glm::vec3 worldUpVec;

    void updateCameraVectors();

};



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  InputClass  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

class Input
{
public:
    Input(GLFWwindow* window);
    ~Input() = default;

    Camera& getCamera() const;
    static void pressKeyboard(GLFWwindow* window);
    static void pressEscape(GLFWwindow* window);
    static void pressDirection(GLFWwindow* window);
    void activateCallback(GLFWwindow* window);
    static void mouseCallback(GLFWwindow* window, double xPosition, double yPosition);
    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
    static void frameBufferSizeCallback(GLFWwindow* window, const int width, const int height);

private:
    static Camera camera;
    static std::pair<float, float> lastMousePosition;
    static bool firstMouse;

};