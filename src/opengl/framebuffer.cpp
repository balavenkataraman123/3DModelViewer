//
// Created by Gianni on 30/06/2024.
//

#include "framebuffer.hpp"

Framebuffer::Framebuffer()
    : m_renderer_id()
    , m_texture_id()
    , m_width()
    , m_height()
    , m_type(Type::NORMAL)
{
}

Framebuffer::Framebuffer(uint32_t width, uint32_t height, Type type)
    : m_renderer_id()
    , m_texture_id()
    , m_width(width)
    , m_height(height)
    , m_type(type)
{
    create();
}

Framebuffer::~Framebuffer()
{
    destroy();
}

Framebuffer::Framebuffer(Framebuffer &&other) noexcept
{
    m_renderer_id = other.m_renderer_id;
    m_texture_id = other.m_texture_id;
    m_width = other.m_width;
    m_height = other.m_height;
    m_type = other.m_type;

    other.m_renderer_id = 0;
    other.m_texture_id = 0;
    other.m_width = 0;
    other.m_height = 0;
}

Framebuffer &Framebuffer::operator=(Framebuffer &&other) noexcept
{
    if (this != &other)
    {
        destroy();

        m_renderer_id = other.m_renderer_id;
        m_texture_id = other.m_texture_id;
        m_width = other.m_width;
        m_height = other.m_height;
        m_type = other.m_type;

        other.m_renderer_id = 0;
        other.m_texture_id = 0;
        other.m_width = 0;
        other.m_height = 0;
    }

    return *this;
}

void Framebuffer::bind() const
{
    glViewport(0, 0, m_width, m_height);
    glBindFramebuffer(GL_FRAMEBUFFER, m_renderer_id);
}

void Framebuffer::unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::resize(uint32_t width, uint32_t height)
{
    if (width == 0 || height == 0)
    {
        std::cout << "FrameBuffer::resize: Attempted to resize framebuffer to " +
                     std::to_string(width) + 'x' + std::to_string(height) << std::endl;

        return;
    }

    if (m_width == width && m_height == height)
        return;

    m_width = width;
    m_height = height;

    create();
}

uint32_t Framebuffer::id() const
{
    return m_renderer_id;
}

uint32_t Framebuffer::texture_id() const
{
    return m_texture_id;
}

uint32_t Framebuffer::width() const
{
    return m_width;
}

uint32_t Framebuffer::height() const
{
    return m_height;
}

void Framebuffer::create()
{
    destroy();

    switch (m_type)
    {
        case Type::NORMAL:
            make_normal_fbo();
            break;
        case Type::MULTISAMPLE:
            make_multisampled_fbo();
            break;
        case Type::DEPTH:
            make_depth_fbo();
            break;
    }
}

void Framebuffer::destroy()
{
    if (m_renderer_id)
    {
        glDeleteTextures(1, &m_texture_id);
        glDeleteFramebuffers(1, &m_renderer_id);

        m_renderer_id = 0;
        m_texture_id = 0;
        m_width = 0;
        m_height = 0;
    }
}

void Framebuffer::make_normal_fbo()
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glCreateFramebuffers(1, &m_renderer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_renderer_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture_id, 0);

    uint32_t frame_buffer_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (frame_buffer_status != GL_FRAMEBUFFER_COMPLETE)
    {
        throw std::runtime_error("Framebuffer::make_normal_fbo: Failed to create the framebuffer\n");
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::make_multisampled_fbo()
{
    constexpr uint32_t SAMPLES = 16;

    glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_texture_id);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, SAMPLES, GL_RGB, m_width, m_height, GL_TRUE);

    glCreateFramebuffers(1, &m_renderer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_renderer_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_texture_id, 0);

    uint32_t frame_buffer_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (frame_buffer_status != GL_FRAMEBUFFER_COMPLETE)
    {
        throw std::runtime_error("Framebuffer::make_multisampled_fbo: Failed to create the framebuffer\n");
    }

    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::make_depth_fbo()
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glCreateFramebuffers(1, &m_renderer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_renderer_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_texture_id, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    uint32_t frame_buffer_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (frame_buffer_status != GL_FRAMEBUFFER_COMPLETE)
    {
        throw std::runtime_error("Framebuffer::make_depth_fbo: Failed to create the framebuffer\n");
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
