#pragma once

#include <glm/mat4x4.hpp>
#include <string>
#include <vector>
#include <map>

#include "Core.hpp"
#include "Shader.hpp"

namespace Coro {

class ShaderProgram {
   private:
    unsigned _id;
	mutable std::map<std::string, int> _cache;

   public:
    ShaderProgram(const std::vector<Ref<Shader>>& shaders);
    void Use() const;

    void SetUniform3f(const std::string& name, float x, float y, float z) const;
    void SetInt(const std::string& name, int data) const;
    void SetFloat(const std::string& name, float data) const;
    void SetMat4(const std::string& name, const glm::mat4& data) const;
	void SetVec3(const std::string& name, const glm::vec3& data) const;
};

}  // namespace Coro