#include "Shader.h"

// ----------------------PUBLIC-----------------------------

Shader::Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource, const bool placehold)
{
    unsigned int vertexShaderID = createAndCompileShader(GL_VERTEX_SHADER, vertexShaderSource), fragmentShaderID = createAndCompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    createShaderProgram(vertexShaderID, fragmentShaderID);
    checkCompileErrors(vertexShaderID, "VERTEX");
    checkCompileErrors(fragmentShaderID, "FRAGMENT");
    checkCompileErrors(shaderProgramID, "PROGRAM");

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexCode, fragmentCode;
    try {
        vertexCode = readShaderCode(vertexPath);
        fragmentCode = readShaderCode(fragmentPath);
    } catch (std::ifstream::failure& error) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << error.what() << std::endl;
    }

    this->Shader::Shader(vertexCode, fragmentCode, true);
}

void Shader::activate() const
{
	glUseProgram(shaderProgramID);
}

unsigned int Shader::getShaderProgramID() const
{
    return shaderProgramID;
}

void Shader::setBool(const std::string& name, const bool value) const
{
	glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, const int value) const
{
	glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, const float value) const
{
	glUniform1f(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& vec2) const
{
    glUniform2fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, &vec2[0]);
}

void Shader::setVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(shaderProgramID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& vec3) const
{
    glUniform3fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, &vec3[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(shaderProgramID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& vec4) const
{
    glUniform4fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, &vec4[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(shaderProgramID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat2) const
{
    glUniformMatrix2fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, GL_FALSE, &mat2[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat3) const
{
    glUniformMatrix3fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, GL_FALSE, &mat3[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat4) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, GL_FALSE, &mat4[0][0]);
}

// ----------------------PRIVATE-----------------------------

std::string Shader::readShaderCode(const std::string& path) const throw (std::ifstream::failure)
{
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(path);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        return std::move(shaderStream.str());
    } catch (std::ifstream::failure& error) {
        throw error;
    }
}

void Shader::checkCompileErrors(const unsigned int shaderID, const std::string& type) const
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else {
        glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderID, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

unsigned int Shader::createAndCompileShader(const int shaderType, const std::string& shaderSource) const
{
    unsigned int shaderID = glCreateShader(shaderType);
    const char* shaderSourceCopy = shaderSource.c_str();
    glShaderSource(shaderID, 1, &shaderSourceCopy, nullptr);
    glCompileShader(shaderID);
    return shaderID;
}

void Shader::createShaderProgram(const unsigned int vertexShaderID, const unsigned int fragmentShaderID)
{
    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);
}