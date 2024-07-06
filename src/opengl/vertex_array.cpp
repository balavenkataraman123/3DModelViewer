//
// Created by Gianni on 30/06/2024.
//

#include "vertex_array.hpp"


VertexArray::VertexArray()
    : m_renderer_id()
{
}

VertexArray::~VertexArray()
{
    if (m_renderer_id)
    {
        glDeleteVertexArrays(1, &m_renderer_id);
    }
}

VertexArray::VertexArray(VertexArray &&other) noexcept
{
    m_renderer_id = other.m_renderer_id;
    other.m_renderer_id = 0;
}

VertexArray &VertexArray::operator=(VertexArray &&other) noexcept
{
    if (this != &other)
    {
        if (m_renderer_id)
        {
            glDeleteVertexArrays(1, &m_renderer_id);
        }

        m_renderer_id = other.m_renderer_id;
        other.m_renderer_id = 0;
    }

    return *this;
}

void VertexArray::create()
{
    if (m_renderer_id)
    {
        glDeleteVertexArrays(1, &m_renderer_id);
    }

    glCreateVertexArrays(1, &m_renderer_id);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_renderer_id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::attach_vertex_buffer(const VertexBuffer &vbo, const VertexBufferLayout &layout) const
{
    bind();
    vbo.bind();

    uint32_t offset = 0;
    uint32_t stride = layout.stride();

    for (const auto& attrib : layout.attributes())
    {
        glEnableVertexAttribArray(attrib.index);
        glVertexAttribPointer(attrib.index, attrib.size, attrib.type, attrib.normalize, stride, reinterpret_cast<void*>(offset));
        offset += attrib.size * utils::gl_sizeof(attrib.type);
    }
}

void VertexArray::attach_index_buffer(const IndexBuffer &ibo) const
{
    bind();
    ibo.bind();

    unbind();
    ibo.unbind();
}

uint32_t VertexArray::id() const
{
    return m_renderer_id;
}
