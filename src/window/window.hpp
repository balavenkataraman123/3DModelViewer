//
// Created by Gianni on 30/06/2024.
//

#ifndef INC_3DMODELVIEWER_WINDOW_HPP
#define INC_3DMODELVIEWER_WINDOW_HPP

#include "window_base.hpp"
#include "../opengl/includes.hpp"
#include "../model/model.hpp"
#include "../camera/camera.hpp"
#include "../utils/utils.hpp"


class Window : public WindowBase
{
public:
    Window(uint32_t width, uint32_t height);
    void run();

private:
    void update(float dt);
    void render();
    void update_model_matrix();
    void fps_counter(float dt);

    static void key_callback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);
    static void resize_callback(GLFWwindow* glfw_window, int width, int height);
    static void mouse_button_callback(GLFWwindow* glfw_window, int button, int action, int mods);
    static void cursor_pos_callback(GLFWwindow* glfw_window, double x, double y);
    static void scroll_callback(GLFWwindow* glfw_window, double x_offset, double y_offset);

private:
    Shader m_shader;
    Model m_3d_model;
    Camera m_camera;

    glm::mat4 m_model_matrix;
    bool m_button_down;
    double m_cursor_pos_x;
    double m_cursor_pos_y;
    float m_rotation_x;
    float m_rotation_y;
    float m_orbit_nav_sensitivity;
    float m_scale;
};


#endif //INC_3DMODELVIEWER_WINDOW_HPP
