//
// Created by Gianni on 1/07/2024.
//

#include "mesh.hpp"


Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices, std::vector<Texture2D> &&textures)
        : m_textures(std::move(textures))
{
    static const VertexBufferLayout layout
    {
        {0, 3, GL_FLOAT, GL_FALSE},
        {1, 3, GL_FLOAT, GL_FALSE},
        {2 , 2, GL_FLOAT, GL_FALSE}
    };

    m_vbo = {vertices.data(), static_cast<uint32_t>(vertices.size() * sizeof(Vertex))};
    m_ibo = {indices.data(), static_cast<uint32_t>(indices.size())};

    m_vao.attach_vertex_buffer(m_vbo, layout);
    m_vao.attach_index_buffer(m_ibo);
}

void Mesh::render(const Shader &shader)
{
    assert(false);
}
