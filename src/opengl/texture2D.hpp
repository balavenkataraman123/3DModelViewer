//
// Created by Gianni on 30/06/2024.
//

#ifndef INC_3DMODELVIEWER_TEXTURE2D_HPP
#define INC_3DMODELVIEWER_TEXTURE2D_HPP

#include <cstdint>
#include <cassert>
#include <stdexcept>
#include <glad/glad.h>


// test const char* copying
// test texture

struct Texture2DSpec;

class Texture2D
{
public:
    Texture2D();
    Texture2D(const char* filename);
    Texture2D(const Texture2DSpec& spec);
    ~Texture2D();

    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;

    Texture2D(Texture2D&& other) noexcept;
    Texture2D& operator=(Texture2D&& other) noexcept;

    void bind(uint32_t slot = 0);
    void unbind(uint32_t slot = 0) const;

    uint32_t id() const;
    int width() const;
    int height() const;

    static void load(const char* filename, uint32_t* id, int* width = nullptr, int* height = nullptr);
    static void load(const Texture2DSpec& spec, uint32_t* id, int* width = nullptr, int* height = nullptr);

private:
    uint32_t m_renderer_id;
    int m_width;
    int m_height;
};


struct Texture2DSpec
{
    const char* filename;
    int wrap;
    int min_filter;
    int mag_filter;
    bool generate_mips;

    Texture2DSpec(const char* filename)
            : filename(filename)
            , wrap(GL_REPEAT)
            , min_filter(GL_LINEAR_MIPMAP_LINEAR)
            , mag_filter(GL_LINEAR)
            , generate_mips(true)
    {
    }
};

#endif //INC_3DMODELVIEWER_TEXTURE2D_HPP
