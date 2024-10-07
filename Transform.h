#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static inline glm::mat4 rotateAndZoom()
{
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
	return trans;
}

glm::mat4 modelMatrix()
{
	glm::mat4 modelMatrix;
	modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	return modelMatrix;
}

glm::mat4 viewMatrix()
{
	glm::mat4 viewMatrix;
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
	return viewMatrix;
}

glm::mat4 projectionMatrix(const float fov, const unsigned int windowWidth, const unsigned int windowHeight)
{
	glm::mat4 projectionMatrix;
	projectionMatrix = glm::perspective(glm::radians(fov), windowWidth / (float)windowHeight, 0.1f, 100.0f);
	return projectionMatrix;
}

void feedMatrixToShader(const unsigned int shaderProgramID, const std::string& matrixType, const glm::mat4& matrix)
{
	int modelLoc = glGetUniformLocation(shaderProgramID, matrixType.c_str());
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}