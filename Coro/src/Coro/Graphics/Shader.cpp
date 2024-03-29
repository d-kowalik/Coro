#include "Shader.hpp"
#include "../Util/FileUtils.hpp"

#include <iostream>

namespace Coro {

Shader::Shader(const std::string& path, GLenum type) : _type(type) {
    const auto data = FileUtils::Read(path);
    if (!data.has_value()) {
        std::cout << "Failed to read shader from file, PATH: " << path
                  << std::endl;
        return;
    }

    const auto str = data.value_or("");
    const char* datacstyle = str.c_str();

    _id = glCreateShader(type);
    glShaderSource(_id, 1, &datacstyle, nullptr);
    glCompileShader(_id);

    int success;
    char infoLog[512];
    glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER COMPILATION FAILED, PATH: " << path
                  << std::endl
                  << "INFO::" << infoLog << std::endl;
    }
}

Shader::~Shader() { Delete(); }

Ref<Shader> Shader::Make(const std::string& path, GLenum type) {
	return MakeRef<Shader>(path, type);
}

void Shader::Delete() {
    _deleted = true;
    glDeleteShader(_id);
}

}  // namespace Coro