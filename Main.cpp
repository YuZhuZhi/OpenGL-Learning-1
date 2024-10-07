#define STB_IMAGE_IMPLEMENTATION
#include <cmath>
#include <iostream>
#include <functional>
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Variables.h"

// -------------------------------------MainFunction-------------------------------------

int main()
{
    #pragma region Initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "22307049", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Input inputManager(window);
    inputManager.activateCallback(window);

    glEnable(GL_DEPTH_TEST);
    #pragma endregion

    #pragma region CreateShaderProgram
    Shader shaderProgram(vertexShaderCodePath, fragmentShaderCodePath);
    #pragma endregion

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    stbi_set_flip_vertically_on_load(true);
    Texture texture1(texture1Path, textrueInform, GL_RGB), texture2(texture2Path, textrueInform, GL_RGBA);

    shaderProgram.activate();
    shaderProgram.setInt("texture1", 0);
    shaderProgram.setInt("texture2", 1);

    #pragma region RenderLoop
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        #pragma region DetectKetboardPress
        Input::pressKeyboard(window);
        #pragma endregion

        #pragma region SetBackgroundColour
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        #pragma endregion

        #pragma region ActivateTexture
        texture1.activate(0);
        texture2.activate(1);
        shaderProgram.activate();
        #pragma endregion

        #pragma region ApplyTransform
        feedMatrixToShader(shaderProgram.getShaderProgramID(), "model", modelMatrix());
        feedMatrixToShader(shaderProgram.getShaderProgramID(), "view", inputManager.getCamera().getViewMatrix());
        shaderProgram.setMat4("projection", projectionMatrix(inputManager.getCamera().getFOV(), windowWidth, windowHeight));
        #pragma endregion

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shaderProgram.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    #pragma endregion

    
    #pragma region Terminate
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
    #pragma endregion
}
