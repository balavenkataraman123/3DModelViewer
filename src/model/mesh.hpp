//
// Created by Gianni on 1/07/2024.
//

#ifndef INC_3DMODELVIEWER_MESH_HPP
#define INC_3DMODELVIEWER_MESH_HPP

#include <vector>
#include "../opengl/includes.hpp"


struct Vertex;

class Mesh
{
public:
    Mesh() = default;
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, std::vector<Texture2D>&& textures);

    void render(const Shader& shader);

private:
    VertexArray m_vao;
    VertexBufferStatic m_vbo;
    IndexBufferStatic m_ibo;
    std::vector<Texture2D> m_textures;
};


struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
};

#endif //INC_3DMODELVIEWER_MESH_HPP
