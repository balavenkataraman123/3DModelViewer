//
// Created by Gianni on 30/06/2024.
//

#include "window.hpp"


static const std::string sample_model {"../assets/models/floating_island.glb"};

Window::Window(uint32_t width, uint32_t height)
    : WindowBase(width, height)
    , m_shader("../shaders/model.vert", "../shaders/model.frag")
    , m_camera(width, height, glm::radians(45.f))
    , m_model_matrix(1.f)
    , m_button_down()
    , m_cursor_pos_x()
    , m_cursor_pos_y()
    , m_rotation_x()
    , m_rotation_y()
    , m_orbit_nav_sensitivity(0.15f)
    , m_scale(1.f)
{
    glfwSetWindowUserPointer(m_glfw_window, this);
    glfwSetKeyCallback(m_glfw_window, key_callback);
    glfwSetWindowSizeCallback(m_glfw_window, resize_callback);
    glfwSetMouseButtonCallback(m_glfw_window, mouse_button_callback);
    glfwSetCursorPosCallback(m_glfw_window, cursor_pos_callback);
    glfwSetScrollCallback(m_glfw_window, scroll_callback);

    m_camera.set_position(0, 0, 4);
    import_new(sample_model);
}

void Window::run()
{
    float last_time = 0;

    while (!glfwWindowShouldClose(m_glfw_window))
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
}

void Window::render()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader.bind();
    m_shader.set_float3("u_view_pos", m_camera.position());
    m_shader.set_mat4("u_proj_view", m_camera.proj_view());
    m_shader.set_mat4("u_model", m_model_matrix);
    m_3d_model.render(m_shader);
    m_shader.unbind();

    glfwSwapBuffers(m_glfw_window);
}

void Window::update_model_matrix()
{
    static constexpr glm::mat4 identity(1.f);

    m_model_matrix = glm::rotate(identity, glm::radians(m_rotation_y), {1.f, 0.f, 0.f});
    m_model_matrix = glm::rotate(m_model_matrix, glm::radians(m_rotation_x), {0.f, 1.f, 0.f});
    m_model_matrix = glm::scale(m_model_matrix, glm::vec3(m_scale));
}

void Window::import_new(const std::string &filename)
{
    m_rotation_x = 0;
    m_rotation_y = 0;
    m_scale = 1.f;
    update_model_matrix();

    m_3d_model.import(filename);
}

void Window::key_callback(GLFWwindow *glfw_window, int key, int scancode, int action, int mods)
{
    Window& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window.m_glfw_window, GLFW_TRUE);
    }

    if (key == GLFW_KEY_O && action == GLFW_PRESS)
    {
        std::string path = utils::file_dialog();

        if (!path.empty())
        {
            window.import_new(path);
        }
    }
}

void Window::resize_callback(GLFWwindow *glfw_window, int width, int height)
{
    Window& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));

    glViewport(0, 0, width, height);

    window.m_camera.resize(width, height);
}

void Window::mouse_button_callback(GLFWwindow *glfw_window, int button, int action, int mods)
{
    Window& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));

    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            window.m_button_down = true;
        }
        else if (action == GLFW_RELEASE)
        {
            window.m_button_down = false;
        }
    }
}

void Window::cursor_pos_callback(GLFWwindow *glfw_window, double x, double y)
{
    Window& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));

    if (window.m_button_down)
    {
        double dx = x - window.m_cursor_pos_x;
        double dy = y - window.m_cursor_pos_y;

        window.m_rotation_x += dx * window.m_orbit_nav_sensitivity;
        window.m_rotation_y += dy * window.m_orbit_nav_sensitivity;

        if (glm::abs(window.m_rotation_y) > 90.f)
        {
            window.m_rotation_y = glm::clamp(window.m_rotation_y, -90.f, 90.f);
        }

        window.update_model_matrix();
    }

    window.m_cursor_pos_x = x;
    window.m_cursor_pos_y = y;
}

void Window::scroll_callback(GLFWwindow *glfw_window, double x_offset, double y_offset)
{
    if (y_offset == 0.f)
        return;

    Window& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));

    window.m_scale += y_offset * window.m_scale / 5.f;
    window.m_scale = glm::clamp(window.m_scale, 0.1f, 10.f);

    window.update_model_matrix();
}
