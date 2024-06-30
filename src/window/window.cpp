//
// Created by Gianni on 30/06/2024.
//

#include "window.hpp"

Window::Window(uint32_t width, uint32_t height)
    : WindowBase(width, height)
    , shader("../shaders/test.vert", "../shaders/test.frag")
    , texture("../assets/textures/lion.png")
{
    float vertices[]
    {
        -0.5, 0.5, 0, 1, // top left
        0.5, 0.5, 1, 1, // top right
        0.5, -0.5, 1, 0, // bottom right
        -0.5, -0.5, 0, 0 // bottom left
    };

    unsigned int indices[] {0, 1, 2, 0, 2, 3};

    vbo = {vertices , sizeof(vertices)};
    ibo = {indices, 6};

    VertexBufferLayout layout
    {
        {0, 2},
        {1, 2}
    };

    vao.attach_vertex_buffer(vbo, layout);
    vao.attach_index_buffer(ibo);
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
}

void Window::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture.bind();
    shader.bind();
    vao.bind();

    glDrawElements(GL_TRIANGLES, ibo.count(), GL_UNSIGNED_INT, nullptr);

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
        std::cout << "Fps: " << frame_count << '\n';
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
