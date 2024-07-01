//
// Created by Gianni on 1/07/2024.
//

#ifndef INC_3DMODELVIEWER_VIEWPORT_HPP
#define INC_3DMODELVIEWER_VIEWPORT_HPP

#include <cstdint>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include "../opengl/includes.hpp"
#include "../camera/perspective_camera.hpp"
#include "../camera/orthographic_camera.hpp"


class Viewport
{
public:
    Viewport(uint32_t width, uint32_t height);

    void update(float dt);
    void render();

    void resize(uint32_t width, uint32_t height);

private:
    void menu_bar();

private:
    VertexArray vao;
    VertexBufferStatic vbo;
    Shader shader;
    PerspectiveCamera pers_camera;
    OrthographicCamera ortho_camera;
    glm::mat4 model;
};


#endif //INC_3DMODELVIEWER_VIEWPORT_HPP
