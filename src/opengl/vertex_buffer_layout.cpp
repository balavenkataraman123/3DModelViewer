//
// Created by Gianni on 30/06/2024.
//

#include "vertex_buffer_layout.hpp"


VertexBufferLayout::VertexBufferLayout()
    : m_stride()
{
}

VertexBufferLayout::VertexBufferLayout(std::initializer_list<attribute> attributes)
    : m_stride()
    , m_attributes(attributes)
{
    for (const auto& attrib : m_attributes)
    {
        increase_stride(attrib);
    }
}

void VertexBufferLayout::add_attribute(const VertexBufferLayout::attribute &attribute)
{
    increase_stride(attribute);
    m_attributes.push_back(attribute);
}

void VertexBufferLayout::add_attribute(VertexBufferLayout::attribute &&attribute)
{
    increase_stride(attribute);
    m_attributes.push_back(std::move(attribute));
}

uint32_t VertexBufferLayout::stride() const
{
    return m_stride;
}

const std::vector<VertexBufferLayout::attribute> &VertexBufferLayout::attributes() const
{
    return m_attributes;
}

void VertexBufferLayout::increase_stride(const VertexBufferLayout::attribute &attribute)
{
    m_stride += attribute.size * utils::gl_sizeof(attribute.type);
}
