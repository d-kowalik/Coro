#include "ShaderProgram.hpp"

#include <glad/glad.h>
#include <iostream>

namespace pge {
ShaderProgram::ShaderProgram(const std::vector<Ref<Shader>>& shaders) {
    _id = glCreateProgram();
    for (const auto& shader : shaders) {
        glAttachShader(_id, shader->GetId());
    }
    glLinkProgram(_id);

    int success;
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINK_FAILED::INFO:" << infoLog
                  << std::endl;
    }
}

void ShaderProgram::Use() const { glUseProgram(_id); }

void ShaderProgram::SetUniform3f(const std::string& name, float x, float y,
                                 float z) const {
    int vertexColorLocation = glGetUniformLocation(_id, name.c_str());
    glUniform3f(vertexColorLocation, x, y, z);
}

void ShaderProgram::SetInt(const std::string& name, int data) const {
    int vertexColorLocation = glGetUniformLocation(_id, name.c_str());
    glUniform1i(vertexColorLocation, data);
}

void ShaderProgram::SetFloat(const std::string& name, float data) const {
    int vertexColorLocation = glGetUniformLocation(_id, name.c_str());
    glUniform1f(vertexColorLocation, data);
}

}  // namespace pge