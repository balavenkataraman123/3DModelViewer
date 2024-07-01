//
// Created by Gianni on 1/07/2024.
//

#include "perspective_camera.hpp"


PerspectiveCamera::PerspectiveCamera()
    : m_projection(1.f)
    , m_width()
    , m_height()
    , m_fovy()
    , m_near()
    , m_far()
{
}

PerspectiveCamera::PerspectiveCamera(float width, float height, float fovy, float near, float far)
    : m_projection(glm::perspective(fovy, width / height, near, far))
    , m_width(width)
    , m_height(height)
    , m_fovy(fovy)
    , m_near(near)
    , m_far(far)
{
}

const glm::mat4 &PerspectiveCamera::projection() const
{
    return m_projection;
}


void PerspectiveCamera::resize(float width, float height)
{
    m_width = width;
    m_height = height;
    m_projection = glm::perspective(m_fovy, m_width / m_height, m_near, m_far);
}
