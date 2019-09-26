#pragma once

#include <vector>

#include "../Core.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

namespace Coro {

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texCoords;
};

class Mesh {
   private:
    std::vector<Vertex> _vertices;
    std::vector<unsigned> _indices;
    std::vector<Ref<Texture>> _textures;
    unsigned _vao, _vbo, _ebo;

   public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices,
         std::vector<Ref<Texture>> textures);
    ~Mesh();

    void Draw(const ShaderProgram& shaderProgram) const;

   private:
    void Setup();
};

}  // namespace Coro