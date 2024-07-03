//
// Created by Gianni on 1/07/2024.
//

#include "mesh.hpp"


Mesh::Mesh(const std::vector<Vertex> &vertices,
           const std::vector<uint32_t> &indices,
           mesh_textures_t &&textures)
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

void Mesh::render(const Shader &shader) const
{
    m_textures.at(aiTextureType_DIFFUSE)->bind(0);

    shader.set_int("u_diffuse_map", 0);

    m_vao.bind();

    glDrawElements(GL_TRIANGLES, m_ibo.count(), GL_UNSIGNED_INT, nullptr);

    m_vao.unbind();

    m_textures.at(aiTextureType_DIFFUSE)->unbind(0);
}
