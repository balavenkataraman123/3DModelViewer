//
// Created by Gianni on 1/07/2024.
//

#include "viewport.hpp"


Viewport::Viewport(uint32_t width, uint32_t height)
    : shader("../shaders/model.vert", "../shaders/model.frag")
    , backpack("../assets/models/backpack/backpack.obj")
    , camera(width, height, glm::radians(45.f))
{
    camera.set_position(0, 0, 4);
}

void Viewport::update(float dt)
{
    menu_bar();

    static glm::vec3 rotation {0, 0, 0};

    ImGui::Begin("debug");
    ImGui::SeparatorText("Model");
    ImGui::SliderFloat3("rotation", reinterpret_cast<float*>(&rotation), -360, 360);
    ImGui::SeparatorText("Lights");
    ImGui::End();

    model = glm::rotate(glm::mat4(1.f), glm::radians(rotation.x), {1, 0, 0});
    model = glm::rotate(model, glm::radians(rotation.y), {0, 1, 0});
    model = glm::rotate(model, glm::radians(rotation.z), {0, 0, 1});
}

void Viewport::render()
{
    shader.bind();
    shader.set_float3("u_view_pos", camera.position());
    shader.set_mat4("u_proj_view", camera.proj_view());
    shader.set_mat4("u_model", model);
    backpack.render(shader);
    shader.unbind();
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

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void Viewport::resize(uint32_t width, uint32_t height)
{
    camera.resize(width, height);
}
