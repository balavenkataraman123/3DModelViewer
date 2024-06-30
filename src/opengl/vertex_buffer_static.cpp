//
// Created by Gianni on 30/06/2024.
//

#include "vertex_buffer_static.hpp"


VertexBufferStatic::VertexBufferStatic()
    : m_renderer_id()
{
}

VertexBufferStatic::VertexBufferStatic(const void *data, uint32_t buffer_size)
    : m_renderer_id()
{
    glCreateBuffers(1, &m_renderer_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBufferStatic::~VertexBufferStatic()
{
    if (m_renderer_id)
    {
        glDeleteBuffers(1, &m_renderer_id);
    }
}

VertexBufferStatic::VertexBufferStatic(VertexBufferStatic &&other) noexcept
{
    m_renderer_id = other.m_renderer_id;
    other.m_renderer_id = 0;
}

VertexBufferStatic &VertexBufferStatic::operator=(VertexBufferStatic &&other) noexcept
{
    if (this != &other)
    {
        if (m_renderer_id)
        {
            glDeleteBuffers(1, &m_renderer_id);
        }

        m_renderer_id = other.m_renderer_id;
        other.m_renderer_id = 0;
    }

    return *this;
}

void VertexBufferStatic::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
}

void VertexBufferStatic::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

uint32_t VertexBufferStatic::id() const
{
    return m_renderer_id;
}
