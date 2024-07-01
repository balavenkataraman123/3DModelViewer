//
// Created by Gianni on 1/07/2024.
//

#include "viewport.hpp"


Viewport::Viewport()
{
}

void Viewport::update(float dt)
{
    menu_bar();
}

void Viewport::render()
{

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
