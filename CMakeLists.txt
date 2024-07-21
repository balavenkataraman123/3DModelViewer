cmake_minimum_required(VERSION 3.28)
project(3DModelViewer)

if (NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message(FATAL_ERROR "This project requires a mingw compiler.")
endif ()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

set(GLAD_DIR ${CMAKE_CURRENT_LIST_DIR}/dependencies/glad)
set(GLFW_DIR ${CMAKE_CURRENT_LIST_DIR}/dependencies/glfw)
set(GLM_DIR ${CMAKE_CURRENT_LIST_DIR}/dependencies/glm)
set(STB_DIR ${CMAKE_CURRENT_LIST_DIR}/dependencies/stb)
set(ASSIMP_DIR ${CMAKE_CURRENT_LIST_DIR}/dependencies/assimp)

file(GLOB_RECURSE GLAD_SRC ${GLAD_DIR}/*.c)
file(GLOB_RECURSE GLAD_HEADERS ${GLAD_DIR}/*.h)
file(GLOB_RECURSE PROJECT_SOURCE_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
file(GLOB_RECURSE PROJECT_HEADER_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.hpp)

add_executable(3DModelViewer
        ${GLAD_SRC}
        ${GLAD_HEADERS}
        ${PROJECT_SOURCE_FILES}
        ${PROJECT_HEADER_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_NAME_DEBUG ${PROJECT_NAME}-d
        OUTPUT_NAME_RELEASE ${PROJECT_NAME})

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
