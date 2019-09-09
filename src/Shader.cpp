#include "Shader.hpp"
#include "FileUtils.hpp"

#include <iostream>

namespace pge {

Shader::Shader(const std::string& path, GLenum type) : _type(type) {
    const auto data = FileUtils::Read(path);
    if (!data.has_value()) {
        std::cout << "Failed to read shader from file, PATH: " << path
                  << std::endl;
        return;
    }

    const char* datacstyle = data.value_or("").c_str();

    _id = glCreateShader(type);
    glShaderSource(_id, 1, &datacstyle, NULL);
    glCompileShader(_id);

    int success;
    char infoLog[512];
    glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cout << "ERROR::SHADER COMPILATION FAILED, PATH: " << path
                  << std::endl;
    }
}

Shader::~Shader() { Delete(); }

void Shader::Delete() {
    _deleted = true;
    glDeleteShader(_id);
}

}  // namespace pge