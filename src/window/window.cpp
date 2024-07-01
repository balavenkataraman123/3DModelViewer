//
// Created by Gianni on 30/06/2024.
//

#include "window.hpp"

Window::Window(uint32_t width, uint32_t height)
    : WindowBase(width, height)
{
    glfwSetWindowUserPointer(m_window, this);
    glfwSetKeyCallback(m_window, key_callback);
}

void Window::run()
{
    float last_time = 0;

    while (!glfwWindowShouldClose(m_window))
    {
        float current_time = glfwGetTime();
        float dt = current_time - last_time;
        last_time = current_time;

        glfwPollEvents();
        update(dt);
        render();
    }
}

void Window::update(float dt)
{
    fps_counter(dt);
    ImGui_Context::begin();
    ImGui::ShowDemoWindow();
    m_viewport.update(dt);
}

void Window::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_viewport.render();

    ImGui_Context::end();
    glfwSwapBuffers(m_window);
}

void Window::fps_counter(float dt)
{
    static float fps_update_time = 0;
    static uint32_t frame_count = 0;

    fps_update_time += dt;
    ++frame_count;

    if (fps_update_time > 1)
    {
        std::cout << "Fps: " << frame_count << std::endl;
        frame_count = 0;
        fps_update_time -= 1;
    }
}

void Window::key_callback(GLFWwindow *p_window, int key, int scancode, int action, int mods)
{
    Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(p_window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window->m_window, GLFW_TRUE);
    }
}
