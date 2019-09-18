#include "Mesh.hpp"

#include <glad/glad.h>
#include <iostream>
#include <string>

namespace Coro {

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices,
           std::vector<Ref<Texture>> textures)
    : _vertices(vertices), _indices(indices), _textures(textures) {
    Setup();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}

void Mesh::Setup() {
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex),
                 &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned),
                 &_indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)(sizeof(Vertex::position)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (void*)(sizeof(Vertex::position) + sizeof(Vertex::color)));
    glEnableVertexAttribArray(2);

    // Unbind everything, VAO will bind it later.
    // Important: UNBIND EBO AFTER UNBINDING VAO OR IT WILL SAVE UNBINDING
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Mesh::Draw(const ShaderProgram& shaderProgram) const {
    shaderProgram.Use();

    int i = 0;
    for (const auto& tex : _textures) {
        std::string name{"texture" + std::to_string(i)};
        shaderProgram.SetInt(name, i);
        glActiveTexture(GL_TEXTURE0 + i++);
        glBindTexture(GL_TEXTURE_2D, tex->GetId());
    }

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

}  // namespace Coro