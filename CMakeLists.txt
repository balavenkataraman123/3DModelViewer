cmake_minimum_required(VERSION 3.28)
project(3DModelViewer)

set(CMAKE_CXX_STANDARD 23)

set(GLAD_DIR ${CMAKE_CURRENT_LIST_DIR}/dependencies/glad)
set(GLFW_DIR ${CMAKE_CURRENT_LIST_DIR}/dependencies/glfw)
set(GLM_DIR ${CMAKE_CURRENT_LIST_DIR}/dependencies/glm)
set(STB_DIR ${CMAKE_CURRENT_LIST_DIR}/dependencies/stb)
set(ASSIMP_DIR ${CMAKE_CURRENT_LIST_DIR}/dependencies/assimp)

file(GLOB_RECURSE GLAD_SRC ${GLAD_DIR}/*.c)
file(GLOB_RECURSE GLAD_HEADERS ${GLAD_DIR}/*.h)

add_executable(3DModelViewer
        ${GLAD_SRC}
        ${GLAD_HEADERS}
        src/main.cpp
        src/opengl/vertex_buffer.hpp
        src/opengl/vertex_buffer_static.cpp
        src/opengl/vertex_buffer_static.hpp
        src/opengl/index_buffer.hpp
        src/opengl/index_buffer_static.cpp
        src/opengl/index_buffer_static.hpp
        src/opengl/vertex_buffer_layout.cpp
        src/opengl/vertex_buffer_layout.hpp
        src/opengl/vertex_array.cpp
        src/opengl/vertex_array.hpp
        src/utils/utils.cpp
        src/utils/utils.hpp
        src/window/window_base.cpp
        src/window/window_base.hpp
        src/window/window.cpp
        src/window/window.hpp
        src/opengl/includes.hpp
        src/opengl/shader.cpp
        src/opengl/shader.hpp
        src/opengl/texture2D.cpp
        src/opengl/texture2D.hpp
        src/opengl/framebuffer.cpp
        src/opengl/framebuffer.hpp
        src/model/mesh.cpp
        src/model/mesh.hpp
        src/model/model.cpp
        src/model/model.hpp
        src/camera/camera.cpp
        src/camera/camera.hpp)

find_package(OpenGL REQUIRED)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        GLFW_INCLUDE_NONE
        STB_IMAGE_WRITE_IMPLEMENTATION
        STB_IMAGE_IMPLEMENTATION)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${GLAD_DIR}/include
        ${GLFW_DIR}/include
        ${GLM_DIR}/include
        ${STB_DIR}/include
        ${ASSIMP_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE
        ${OPENGL_LIBRARIES}
        ${GLFW_DIR}/lib/libglfw3.a
        ${ASSIMP_DIR}/lib/libassimp.a
        ${ASSIMP_DIR}/lib/libzlibstatic.a)

target_link_options(${PROJECT_NAME} PRIVATE -static "-Wl,--allow-multiple-definition")
