//
// Created by Gianni on 4/07/2024.
//

#include "camera.hpp"


Camera::Camera()
    : m_projection()
    , m_view()
    , m_proj_view()
    , m_position()
{
}

Camera::Camera(float width, float height, float fov, float near, float far)
    : m_projection(glm::perspective(fov, width / height, near, far))
    , m_view()
    , m_proj_view(m_projection)
    , m_position()
{
}

Camera::Camera(float left, float right, float bottom, float top, float near, float far)
    : m_projection(glm::ortho(left, right, bottom, top, near, far))
    , m_view()
    , m_proj_view(m_projection)
    , m_position()
{
}

void Camera::set_position(const glm::vec3 &position)
{
    m_position = position;
    recalculate_view();
}

void Camera::set_position(float x, float y, float z)
{
    set_position({x, y, z});
}

void Camera::resize(float width, float height)
{
    // todo: implement
}

const glm::mat4 &Camera::projection() const
{
    return m_projection;
}

const glm::mat4 &Camera::view() const
{
    return m_view;
}

const glm::mat4 &Camera::proj_view() const
{
    return m_proj_view;
}

const glm::vec3 &Camera::position() const
{
    return m_position;
}

void Camera::recalculate_view()
{
    static constexpr glm::mat4 identity(1.f);

    glm::mat4 transform = glm::translate(identity, m_position);
    m_view = glm::inverse(transform);

    m_proj_view = m_projection * m_view;
}
