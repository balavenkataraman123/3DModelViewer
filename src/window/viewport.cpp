//
// Created by Gianni on 1/07/2024.
//

#include "viewport.hpp"


Viewport::Viewport(uint32_t width, uint32_t height)
    : shader("../shaders/model.vert", "../shaders/model.frag")
    , backpack("../assets/models/backpack/backpack.obj")
    , depth_fbo(width, height, Framebuffer::Type::DEPTH)
    , dir_light(-1, -1.f, 0)
    , camera(width, height, glm::radians(45.f))
{
    camera.set_position(0, 0, 4);

    light_proj_view = glm::ortho(-10.f, 10.f, -10.f, 10.f, 0.1f, 100.f)
                      * glm::lookAt(-5.f * dir_light, glm::vec3(0.f), glm::vec3(0, 1.f, 0));
}

void Viewport::update(float dt)
{
    menu_bar();

    static glm::vec3 rotation {0, 0, 0};

    ImGui::Begin("debug");
    ImGui::SeparatorText("Model");
    ImGui::SliderFloat3("rotation", reinterpret_cast<float*>(&rotation), -360, 360);
    ImGui::SeparatorText("Lights");
    ImGui::SliderFloat3("dir light", reinterpret_cast<float*>(&dir_light), -10, 10);
    ImGui::End();

    model = glm::rotate(glm::mat4(1.f), glm::radians(rotation.x), {1, 0, 0});
    model = glm::rotate(model, glm::radians(rotation.y), {0, 1, 0});
    model = glm::rotate(model, glm::radians(rotation.z), {0, 0, 1});
}

void Viewport::render()
{
    shader.bind();
    shader.set_float("u_kl", 0.014f);
    shader.set_float("u_kq", 0.0007f);
    shader.set_float3("u_view_pos", camera.position());
    shader.set_mat4("u_proj_view", camera.proj_view());
    shader.set_mat4("u_model", model);
    shader.set_float3("u_dir_light_dir", dir_light);
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
    camera.resize(width, height);
}
