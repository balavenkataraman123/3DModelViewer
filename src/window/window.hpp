//
// Created by Gianni on 30/06/2024.
//

#ifndef INC_3DMODELVIEWER_WINDOW_HPP
#define INC_3DMODELVIEWER_WINDOW_HPP

#include "window_base.hpp"
#include "../imgui/im_gui_context.hpp"
#include "../opengl/includes.hpp"
#include "../model/model.hpp"
#include "../camera/camera.hpp"


class Window : public WindowBase
{
public:
    Window(uint32_t width, uint32_t height);
    void run();

private:
    void update(float dt);
    void render();
    void fps_counter(float dt);
    void menu_bar();
    void update_model_matrix();

    static void key_callback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);
    static void resize_callback(GLFWwindow* glfw_window, int width, int height);
    static void mouse_button_callback(GLFWwindow* glfw_window, int button, int action, int mods);

private:
    Shader shader;
    Model backpack;
    Camera camera;
    glm::mat4 model;
};


#endif //INC_3DMODELVIEWER_WINDOW_HPP
