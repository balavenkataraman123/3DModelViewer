//
// Created by Gianni on 1/07/2024.
//

#include "viewport.hpp"


Viewport::Viewport(uint32_t width, uint32_t height)
    : m_fbo(width, height, Framebuffer::Type::MULTISAMPLE)
    , m_intermediate_fbo(width, height, Framebuffer::Type::NORMAL)
    , m_width(width)
    , m_height(height)
    , shader("../shaders/test.vert", "../shaders/test.frag")
    , texture("../assets/textures/lion.png")
{
    float vertices[]
    {
            -0.5, 0.5, 0, 1, // top left
            0.5, 0.5, 1, 1, // top right
            0.5, -0.5, 1, 0, // bottom right
            -0.5, -0.5, 0, 0 // bottom left
    };

    unsigned int indices[] {0, 1, 2, 0, 2, 3};

    vbo = {vertices , sizeof(vertices)};
    ibo = {indices, 6};

    VertexBufferLayout layout
    {
            {0, 2},
            {1, 2}
    };

    vao.attach_vertex_buffer(vbo, layout);
    vao.attach_index_buffer(ibo);
}

void Viewport::update(float dt)
{

}

void Viewport::render()
{
    pre_render();

    texture.bind();
    shader.bind();
    vao.bind();

    glDrawElements(GL_TRIANGLES, ibo.count(), GL_UNSIGNED_INT, nullptr);

    post_render();
}

void Viewport::pre_render()
{
    int flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse;
    ImGui::Begin("Viewport", nullptr, flags);

    glm::uvec2 window_size
    {
        static_cast<uint32_t>(ImGui::GetContentRegionAvail().x),
        static_cast<uint32_t>(ImGui::GetContentRegionAvail().y)
    };

    if (m_width != window_size.x || m_height != window_size.y)
    {

        if (ImGui::IsWindowDocked() || ImGui::IsMouseReleased(ImGuiMouseButton_Left))
        {
            m_width = window_size.x;
            m_height = window_size.y;
            resize();
        }
    }

    m_fbo.bind();

    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Viewport::post_render()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_intermediate_fbo.id());
    glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    m_fbo.unbind();

    ImGui::Image(reinterpret_cast<void*>(m_intermediate_fbo.id()), ImVec2(m_width, m_height), ImVec2(0.f, 1.f), ImVec2(1.f, 0.f));
    ImGui::End();
}

void Viewport::resize()
{
    m_fbo.resize(m_width, m_height);
    m_intermediate_fbo.resize(m_width, m_height);
}
