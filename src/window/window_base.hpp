//
// Created by Gianni on 30/06/2024.
//

#ifndef INC_3DMODELVIEWER_WINDOW_BASE_HPP
#define INC_3DMODELVIEWER_WINDOW_BASE_HPP

#include <stdexcept>
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include "../imgui/im_gui_context.hpp"


class WindowBase
{
public:
    WindowBase(uint32_t width, uint32_t height);
    virtual ~WindowBase();

protected:
    GLFWwindow* m_glfw_window;
};


#endif //INC_3DMODELVIEWER_WINDOW_BASE_HPP
