//
// Created by Gianni on 30/06/2024.
//

#ifndef INC_3DMODELVIEWER_WINDOW_HPP
#define INC_3DMODELVIEWER_WINDOW_HPP

#include "window_base.hpp"
#include "viewport.hpp"
#include "../imgui/im_gui_context.hpp"


class Window : public WindowBase
{
public:
    Window(uint32_t width, uint32_t height);
    void run();

private:
    void update(float dt);
    void render();
    void fps_counter(float dt);

    static void key_callback(GLFWwindow* p_window, int key, int scancode, int action, int mods);

private:
    Viewport m_viewport;
};


#endif //INC_3DMODELVIEWER_WINDOW_HPP
