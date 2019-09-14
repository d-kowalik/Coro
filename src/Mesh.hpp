#pragma once

#include <vector>

#include "ShaderProgram.hpp"

namespace pge {

struct vec2 {
    float x, y;
};

struct vec3 {
    float x, y, z;
};

struct Vertex {
    vec3 position;
    vec3 color;
    vec2 texCoords;
};

struct Texture {
    unsigned id;
};

class Mesh {
   private:
    std::vector<Vertex> _vertices;
    std::vector<unsigned> _indices;
    std::vector<Texture> _textures;
    unsigned _vao, _vbo, _ebo;

   public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices,
         std::vector<Texture> textures);
    ~Mesh();

    void Draw(const ShaderProgram& shaderProgram) const;

   private:
    void Setup();
};

}  // namespace pge