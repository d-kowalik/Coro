#pragma once

#include <string>
#include <vector>

#include "Core.hpp"
#include "Shader.hpp"

namespace pge {

class ShaderProgram {
   private:
    unsigned _id;

   public:
    ShaderProgram(const std::vector<Ref<Shader>>& shaders);
    void Use() const;
    void SetUniform3f(const std::string& name, float x, float y, float z) const;
    void SetInt(const std::string& name, int data) const;
    void SetFloat(const std::string& name, float data) const;
};

}  // namespace pge