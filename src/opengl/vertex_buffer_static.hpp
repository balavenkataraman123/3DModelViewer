//
// Created by Gianni on 30/06/2024.
//

#ifndef INC_3DMODELVIEWER_VERTEX_BUFFER_STATIC_HPP
#define INC_3DMODELVIEWER_VERTEX_BUFFER_STATIC_HPP

#include <cstdint>
#include <glad/glad.h>
#include "vertex_buffer.hpp"


class VertexBufferStatic : public VertexBuffer
{
public:
    VertexBufferStatic();
    VertexBufferStatic(const void* data, uint32_t buffer_size);
    ~VertexBufferStatic() override;

    VertexBufferStatic(VertexBufferStatic&& other) noexcept;
    VertexBufferStatic& operator=(VertexBufferStatic&& other) noexcept;

    VertexBufferStatic(const VertexBufferStatic&) = delete;
    VertexBufferStatic& operator=(const VertexBufferStatic&) = delete;

    void bind() const override;
    void unbind() const override;

    uint32_t id() const override;

private:
    uint32_t m_renderer_id;
};


#endif //INC_3DMODELVIEWER_VERTEX_BUFFER_STATIC_HPP
