//
// Created by Gianni on 30/06/2024.
//

#ifndef INC_3DMODELVIEWER_FRAMEBUFFER_HPP
#define INC_3DMODELVIEWER_FRAMEBUFFER_HPP

#include <cstdint>
#include <iostream>
#include <cassert>
#include <glad/glad.h>


class Framebuffer
{
public:
    enum class Type
    {
        NORMAL,
        MULTISAMPLE,
        DEPTH
    };

public:
    Framebuffer();
    Framebuffer(uint32_t width, uint32_t height, Type type);
    ~Framebuffer();

    Framebuffer(Framebuffer&& other) noexcept;
    Framebuffer& operator=(Framebuffer&& other) noexcept;

    Framebuffer(const Framebuffer&) = delete;
    Framebuffer& operator=(const Framebuffer&) = delete;

    void bind() const;
    void unbind() const;

    void resize(uint32_t width, uint32_t height);

    uint32_t id() const;
    uint32_t texture_id() const;
    uint32_t width() const;
    uint32_t height() const;

private:
    void create();
    void destroy();

    void make_normal_fbo();
    void make_multisampled_fbo();
    void make_depth_fbo();

private:
    uint32_t m_renderer_id;
    uint32_t m_texture_id;
    uint32_t m_width;
    uint32_t m_height;
    Type m_type;
};


#endif //INC_3DMODELVIEWER_FRAMEBUFFER_HPP
