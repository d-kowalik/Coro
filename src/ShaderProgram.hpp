#pragma once

#include <string>
#include <vector>

#include "Shader.hpp"

namespace pge {

class ShaderProgram {
   private:
    unsigned _id;

   public:
    ShaderProgram(const std::vector<Shader>& shaders);
    void Use() const;
    void SetUniform3f(const std::string& name, float x, float y, float z) const;
};

}  // namespace pge