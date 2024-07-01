//
// Created by Gianni on 1/07/2024.
//

#include "orthographic_camera.hpp"


OrthographicCamera::OrthographicCamera()
    : m_projection(1.f)
{
}

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
{
    m_projection = glm::ortho(left, right, bottom, top, near, far);
}

const glm::mat4 &OrthographicCamera::projection() const
{
    return m_projection;
}
