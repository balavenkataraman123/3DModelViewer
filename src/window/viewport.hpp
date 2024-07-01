//
// Created by Gianni on 1/07/2024.
//

#ifndef INC_3DMODELVIEWER_VIEWPORT_HPP
#define INC_3DMODELVIEWER_VIEWPORT_HPP

#include <cstdint>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include "../opengl/includes.hpp"


class Viewport
{
public:
    Viewport();

    void update(float dt);
    void render();

private:
    void menu_bar();
};


#endif //INC_3DMODELVIEWER_VIEWPORT_HPP
