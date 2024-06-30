//
// Created by Gianni on 30/06/2024.
//

#ifndef INC_3DMODELVIEWER_VERTEX_BUFFER_HPP
#define INC_3DMODELVIEWER_VERTEX_BUFFER_HPP

#include <cstdint>


class VertexBuffer
{
public:
    virtual ~VertexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual uint32_t id() const = 0;
};

#endif //INC_3DMODELVIEWER_VERTEX_BUFFER_HPP
