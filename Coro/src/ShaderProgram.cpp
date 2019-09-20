#include "ShaderProgram.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace Coro {
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
	if (_cache.find(name) == _cache.end()) _cache[name] = glGetUniformLocation(_id, name.c_str());
	
    glUniform3f(_cache[name], x, y, z);
}

void ShaderProgram::SetInt(const std::string& name, int data) const {
	if (_cache.find(name) == _cache.end()) _cache[name] = glGetUniformLocation(_id, name.c_str());

    glUniform1i(_cache[name], data);
}

void ShaderProgram::SetFloat(const std::string& name, float data) const {
	if (_cache.find(name) == _cache.end()) _cache[name] = glGetUniformLocation(_id, name.c_str());

	glUniform1f(_cache[name], data);
}

void ShaderProgram::SetMat4(const std::string& name,
                            const glm::mat4& data) const {
	if (_cache.find(name) == _cache.end()) _cache[name] = glGetUniformLocation(_id, name.c_str());

	glUniformMatrix4fv(_cache[name], 1, GL_FALSE, glm::value_ptr(data));
}

void ShaderProgram::SetVec3(const std::string& name, const glm::vec3& data) const {
	if (_cache.find(name) == _cache.end()) _cache[name] = glGetUniformLocation(_id, name.c_str());

	glUniform3f(_cache[name], data.x, data.y, data.z);
}

}  // namespace Coro