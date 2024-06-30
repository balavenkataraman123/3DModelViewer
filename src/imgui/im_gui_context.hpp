//
// Created by Gianni on 30/06/2024.
//

#ifndef INC_3DMODELVIEWER_IM_GUI_CONTEXT_HPP
#define INC_3DMODELVIEWER_IM_GUI_CONTEXT_HPP

#include <glfw/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


namespace ImGui_Context
{
    void init(GLFWwindow* window);
    void terminate();

    void begin();
    void end();
};


#endif //INC_3DMODELVIEWER_IM_GUI_CONTEXT_HPP
