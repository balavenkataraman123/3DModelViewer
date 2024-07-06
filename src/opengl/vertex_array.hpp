//
// Created by Gianni on 30/06/2024.
//

#ifndef INC_3DMODELVIEWER_VERTEX_ARRAY_HPP
#define INC_3DMODELVIEWER_VERTEX_ARRAY_HPP

#include "vertex_buffer.hpp"
#include "index_buffer.hpp"
#include "vertex_buffer_layout.hpp"


class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    VertexArray(VertexArray&& other) noexcept;
    VertexArray& operator=(VertexArray&& other) noexcept;

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    void create();
    void bind() const;
    void unbind() const;

    void attach_vertex_buffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) const;
    void attach_index_buffer(const IndexBuffer& ibo) const;

    uint32_t id() const;

private:
    uint32_t m_renderer_id;
};


#endif //INC_3DMODELVIEWER_VERTEX_ARRAY_HPP
