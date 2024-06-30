//
// Created by Gianni on 30/06/2024.
//

#include "index_buffer_static.hpp"


IndexBufferStatic::IndexBufferStatic()
    : m_renderer_id()
    , m_count()
{
}

IndexBufferStatic::IndexBufferStatic(const void *data, uint32_t count)
    : m_renderer_id()
    , m_count(count)
{
    glCreateBuffers(1, &m_renderer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(uint32_t), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBufferStatic::~IndexBufferStatic()
{
    if (m_renderer_id)
    {
        glDeleteBuffers(1, &m_renderer_id);
    }
}

IndexBufferStatic::IndexBufferStatic(IndexBufferStatic &&other) noexcept
{
    m_renderer_id = other.m_renderer_id;
    m_count = other.m_count;

    other.m_renderer_id = 0;
    other.m_count = 0;
}

IndexBufferStatic &IndexBufferStatic::operator=(IndexBufferStatic &&other) noexcept
{
    if (this != &other)
    {
        if (m_renderer_id)
        {
            glDeleteBuffers(1, &m_renderer_id);
        }

        m_renderer_id = other.m_renderer_id;
        m_count = other.m_count;

        other.m_renderer_id = 0;
        other.m_count = 0;
    }

    return *this;
}

void IndexBufferStatic::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
}

void IndexBufferStatic::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t IndexBufferStatic::id() const
{
    return m_renderer_id;
}

uint32_t IndexBufferStatic::count() const
{
    return m_count;
}
