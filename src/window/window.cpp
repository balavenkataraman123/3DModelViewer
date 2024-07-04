//
// Created by Gianni on 30/06/2024.
//

#include "window.hpp"

Window::Window(uint32_t width, uint32_t height)
    : WindowBase(width, height)
    , shader("../shaders/model.vert", "../shaders/model.frag")
    , backpack("../assets/models/backpack/backpack.obj")
    , camera(width, height, glm::radians(45.f))
{
    glfwSetWindowUserPointer(m_glfw_window, this);
    glfwSetKeyCallback(m_glfw_window, key_callback);
    glfwSetWindowSizeCallback(m_glfw_window, resize_callback);
    glfwSetMouseButtonCallback(m_glfw_window, mouse_button_callback);
    glfwSetCursorPosCallback(m_glfw_window, cursor_pos_callback);
    glfwSetScrollCallback(m_glfw_window, scroll_callback);
    camera.set_position(0, 0, 4);
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
    ImGui_Context::begin();
    fps_counter(dt);
    menu_bar();
    update_model_matrix();
}

void Window::render()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.bind();
    shader.set_float3("u_view_pos", camera.position());
    shader.set_mat4("u_proj_view", camera.proj_view());
    shader.set_mat4("u_model", model);
    backpack.render(shader);
    shader.unbind();

    ImGui_Context::end();
    glfwSwapBuffers(m_glfw_window);
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

void Window::menu_bar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open...", "Ctrl+O"))
            {
                puts("Open");
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Settings"))
        {
            if (ImGui::MenuItem("Fit to View", "Ctrl+V"))
            {
                puts("Fit to view");
            }

            if (ImGui::MenuItem("Fix Orientation", "Ctrl+F"))
            {
                puts("Fix orientation");
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void Window::update_model_matrix()
{
    static glm::vec3 rotation {0, 0, 0};

    ImGui::Begin("debug");
    ImGui::SeparatorText("Model");
    ImGui::SliderFloat3("rotation", reinterpret_cast<float*>(&rotation), -360, 360);
    ImGui::End();

    model = glm::rotate(glm::mat4(1.f), glm::radians(rotation.x), {1, 0, 0});
    model = glm::rotate(model, glm::radians(rotation.y), {0, 1, 0});
    model = glm::rotate(model, glm::radians(rotation.z), {0, 0, 1});
}

void Window::key_callback(GLFWwindow *glfw_window, int key, int scancode, int action, int mods)
{
    ImGui_ImplGlfw_KeyCallback(glfw_window, key, scancode, action, mods);

    Window& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window.m_glfw_window, GLFW_TRUE);
    }
}

void Window::resize_callback(GLFWwindow *glfw_window, int width, int height)
{
    Window& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));

    glViewport(0, 0, width, height);

    window.camera.resize(width, height);
}

void Window::mouse_button_callback(GLFWwindow *glfw_window, int button, int action, int mods)
{
    ImGui_ImplGlfw_MouseButtonCallback(glfw_window, button, action, mods);

    Window& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));

    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            puts("press");
        }
        else if (action == GLFW_RELEASE)
        {
            puts("release");
        }
    }
}

void Window::cursor_pos_callback(GLFWwindow *glfw_window, double x, double y)
{
    ImGui_ImplGlfw_CursorPosCallback(glfw_window, x, y);

    Window& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));

}

void Window::scroll_callback(GLFWwindow *glfw_window, double x_offset, double y_offset)
{
    ImGui_ImplGlfw_ScrollCallback(glfw_window, x_offset, y_offset);

    Window& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
}
