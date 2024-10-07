#pragma once
#include <fstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Shader
{
public:
    Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource, const bool placehold);
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
    Shader(const Shader&) = delete;
	~Shader() = default;

    void activate() const;
    unsigned int getShaderProgramID() const;
    void setBool(const std::string& name, const bool value) const;
    void setInt(const std::string& name, const int value) const;
    void setFloat(const std::string& name, const float value) const;

    void setVec2(const std::string& name, const glm::vec2& vec2) const;
    void setVec2(const std::string& name, float x, float y) const;
    void setVec3(const std::string& name, const glm::vec3& vec3) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, const glm::vec4& vec4) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    void setMat2(const std::string& name, const glm::mat2& mat2) const;
    void setMat3(const std::string& name, const glm::mat3& mat3) const;
    void setMat4(const std::string& name, const glm::mat4& mat4) const;

private:
    unsigned int shaderProgramID;

    std::string readShaderCode(const std::string& path) const throw (std::ifstream::failure);
    void checkCompileErrors(const unsigned int shaderID, const std::string& type) const;
    unsigned int createAndCompileShader(const int shaderType, const std::string& shaderSource) const;
    void createShaderProgram(const unsigned int vertexShaderID, const unsigned int fragmentShaderID);
};
