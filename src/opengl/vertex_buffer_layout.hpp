//
// Created by Gianni on 30/06/2024.
//

#ifndef INC_3DMODELVIEWER_VERTEX_BUFFER_LAYOUT_HPP
#define INC_3DMODELVIEWER_VERTEX_BUFFER_LAYOUT_HPP

#include <cstdint>
#include <initializer_list>
#include <vector>
#include <glad/glad.h>
#include "../utils/utils.hpp"


class VertexBufferLayout
{
public:
    struct attribute
    {
        uint32_t index;
        int size;
        uint32_t type;
        uint8_t normalize;
    };

public:
    VertexBufferLayout();
    VertexBufferLayout(std::initializer_list<attribute> attributes);

    void add_attribute(const attribute& attribute);
    void add_attribute(attribute&& attribute);

    uint32_t stride() const;
    const std::vector<attribute>& attributes() const;

private:
    void increase_stride(const attribute& attribute);

private:
    std::vector<attribute> m_attributes;
    uint32_t m_stride;
};


#endif //INC_3DMODELVIEWER_VERTEX_BUFFER_LAYOUT_HPP
