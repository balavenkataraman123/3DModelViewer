//
// Created by Gianni on 30/06/2024.
//

#include "texture2D.hpp"
#include <stb/stb_image.h>


Texture2D::Texture2D()
    : m_renderer_id()
    , m_width()
    , m_height()
{
}

Texture2D::Texture2D(const char *filename)
    : Texture2D()
{
    load(filename, &m_renderer_id, &m_width, &m_height);
}

Texture2D::Texture2D(const Texture2DSpec &spec)
    : Texture2D()
{
    load(spec, &m_renderer_id, &m_width, &m_height);
}

Texture2D::~Texture2D()
{
    if (m_renderer_id)
    {
        glDeleteTextures(1, &m_renderer_id);
    }
}

Texture2D::Texture2D(Texture2D &&other) noexcept
    : Texture2D()
{
    std::swap(m_renderer_id, other.m_renderer_id);
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
}

Texture2D &Texture2D::operator=(Texture2D &&other) noexcept
{
    if (this != &other)
    {
        if (m_renderer_id)
        {
            glDeleteTextures(1, &m_renderer_id);
        }

        m_renderer_id = other.m_renderer_id;
        m_width = other.m_width;
        m_height = other.m_height;

        other.m_renderer_id = 0;
        other.m_width = 0;
        other.m_height = 0;
    }

    return *this;
}

void Texture2D::bind(uint32_t slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_renderer_id);
}

void Texture2D::unbind(uint32_t slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, 0);
}

uint32_t Texture2D::id() const
{
    return m_renderer_id;
}

int Texture2D::width() const
{
    return m_width;
}

int Texture2D::height() const
{
    return m_height;
}

void Texture2D::load(const char *filename, uint32_t *id, int *width, int *height)
{
    load(Texture2DSpec(filename), id, width, height);
}

void Texture2D::load(const Texture2DSpec &spec, uint32_t *id, int *width, int *height)
{
    stbi_set_flip_vertically_on_load(spec.flip_uvs);

    int _w, _h;

    int channels;
    uint8_t* data = stbi_load(spec.filename, width? width : &_w, height? height : &_h, &channels, 0);

    if (!data)
    {
        throw std::runtime_error("Texture2D::load: Failed to load texture \"" + std::string(spec.filename) + "\"");
    }

    int format;
    switch (channels)
    {
        case 1: format = GL_RED; break;
        case 2: format = GL_RG; break;
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        default: assert(false);
    }

    glCreateTextures(GL_TEXTURE_2D, 1, id);
    glBindTexture(GL_TEXTURE_2D, *id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, spec.wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, spec.wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, spec.min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, spec.mag_filter);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width? *width : _w, height? *height : _h, 0, format, GL_UNSIGNED_BYTE, data);

    if (spec.generate_mips)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
}
