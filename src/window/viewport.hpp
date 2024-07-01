//
// Created by Gianni on 1/07/2024.
//

#ifndef INC_3DMODELVIEWER_VIEWPORT_HPP
#define INC_3DMODELVIEWER_VIEWPORT_HPP

#include <cstdint>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include "../opengl/includes.hpp"


class Viewport
{
public:
    Viewport(uint32_t width, uint32_t height);

    void update(float dt);
    void render();

private:
    void pre_render();
    void post_render();
    void resize();

private:
    Framebuffer m_fbo;
    Framebuffer m_intermediate_fbo;

    uint32_t m_width;
    uint32_t m_height;

    VertexArray vao;
    VertexBufferStatic vbo;
    IndexBufferStatic ibo;
    Shader shader;
    Texture2D texture;
};


#endif //INC_3DMODELVIEWER_VIEWPORT_HPP
