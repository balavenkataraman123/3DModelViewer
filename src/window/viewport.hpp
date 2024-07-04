//
// Created by Gianni on 1/07/2024.
//

#ifndef INC_3DMODELVIEWER_VIEWPORT_HPP
#define INC_3DMODELVIEWER_VIEWPORT_HPP

#include <cstdint>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <glfw/glfw3.h>
#include "../opengl/includes.hpp"
#include "../model/model.hpp"
#include "../camera/camera.hpp"


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
    Shader shader;
    Model backpack;
    Camera camera;
    Framebuffer depth_fbo;

    glm::mat4 model;
    glm::vec3 dir_light;

    glm::mat4 light_proj_view;
};


#endif //INC_3DMODELVIEWER_VIEWPORT_HPP
