//
// Created by Gianni on 30/06/2024.
//

#include "utils.hpp"
#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3native.h>
#include <algorithm>


namespace utils
{
    uint32_t gl_sizeof(uint32_t type)
    {
        switch (type)
        {
            case GL_FLOAT: return sizeof(float);
            case GL_UNSIGNED_INT: return sizeof(unsigned int);
            case GL_INT: return sizeof(int);
            case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
            case GL_BYTE: return sizeof(char);
            case GL_DOUBLE: return sizeof(double);
            default: assert(false);
        }
    }

    std::string file_dialog()
    {
        char filename[260] {};
        OPENFILENAME ofn;
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lpstrFile = filename;
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = glfwGetWin32Window(glfwGetCurrentContext());
        ofn.nMaxFile = sizeof(filename);
        ofn.lpstrFilter = "3D Files\0*.fbx;*.obj;*.dae;*.gltf;*.glb;*.3ds\0";
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

        if (GetOpenFileName(&ofn) == TRUE)
        {
            std::filesystem::path abs_path(filename);
            std::filesystem::path cwd(std::filesystem::current_path());
            std::filesystem::path rel_path(std::filesystem::relative(abs_path, cwd));
            std::string result = rel_path.string();
            std::replace(result.begin(), result.end(), '\\', '/');

            return result;
        }

        return {};
    }
}
