//
// Created by Gianni on 1/07/2024.
//

#include "viewport.hpp"


Viewport::Viewport(uint32_t width, uint32_t height)
    : shader("../shaders/model.vert", "../shaders/model.frag")
    , pers_camera(static_cast<float>(width), static_cast<float>(height), glm::radians(45.f))
    , ortho_camera(-1.f, 1.f, -1.f, 1.f)
    , backpack("../assets/models/backpack/backpack.obj")
{
}

void Viewport::update(float dt)
{
    menu_bar();

    static glm::vec3 translation {0, 0, 0};

    ImGui::Begin("debug");
    ImGui::SliderFloat3("translation", reinterpret_cast<float*>(&translation), -10, 10);
    ImGui::End();

    model = glm::translate(glm::mat4(1.f), translation);
}

void Viewport::render()
{
    shader.bind();
    shader.set_mat4("u_proj", pers_camera.projection());
    shader.set_mat4("u_model", model);
    backpack.render(shader);
}

void Viewport::menu_bar()
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

            if (ImGui::BeginMenu("Projection"))
            {
                if (ImGui::MenuItem("Perspective", nullptr, true))
                {

                }

                if (ImGui::MenuItem("Orthographic", nullptr, false))
                {

                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Navigation"))
            {
                if (ImGui::MenuItem("Orbit", nullptr, true))
                {

                }

                if (ImGui::MenuItem("First Person", nullptr, false))
                {

                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void Viewport::resize(uint32_t width, uint32_t height)
{
    pers_camera.resize(width, height);
}
