//
// Created by Gianni on 30/06/2024.
//

#ifndef INC_3DMODELVIEWER_INDEX_BUFFER_STATIC_HPP
#define INC_3DMODELVIEWER_INDEX_BUFFER_STATIC_HPP

#include <glad/glad.h>
#include "index_buffer.hpp"


class IndexBufferStatic : public IndexBuffer
{
public:
    IndexBufferStatic();
    IndexBufferStatic(const void* data, uint32_t count);
    ~IndexBufferStatic() override;

    IndexBufferStatic(IndexBufferStatic&& other) noexcept;
    IndexBufferStatic& operator=(IndexBufferStatic&& other) noexcept;

    IndexBufferStatic(const IndexBufferStatic&) = delete;
    IndexBufferStatic& operator=(const IndexBufferStatic&) = delete;

    void bind() const override;
    void unbind() const override;

    uint32_t id() const override;
    uint32_t count() const override;

private:
    uint32_t m_renderer_id;
    uint32_t m_count;
};


#endif //INC_3DMODELVIEWER_INDEX_BUFFER_STATIC_HPP
