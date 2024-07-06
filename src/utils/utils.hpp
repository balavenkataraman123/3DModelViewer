//
// Created by Gianni on 30/06/2024.
//

#ifndef INC_3DMODELVIEWER_UTILS_HPP
#define INC_3DMODELVIEWER_UTILS_HPP

#include <cstdint>
#include <cassert>
#include <string>
#include <filesystem>
#include <windows.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>


namespace utils
{
    uint32_t gl_sizeof(uint32_t type);
    std::string file_dialog();
}


#endif //INC_3DMODELVIEWER_UTILS_HPP
