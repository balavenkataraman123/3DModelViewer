//
// Created by Gianni on 1/07/2024.
//

#ifndef INC_3DMODELVIEWER_PERSPECTIVE_CAMERA_HPP
#define INC_3DMODELVIEWER_PERSPECTIVE_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class PerspectiveCamera
{
public:
    PerspectiveCamera();
    PerspectiveCamera(float width, float height, float fovy, float near = 0.1f, float far = 100.f);

    void resize(float width, float height);

    const glm::mat4& projection() const;

private:
    glm::mat4 m_projection;
    float m_width;
    float m_height;
    float m_fovy;
    float m_near;
    float m_far;
};


#endif //INC_3DMODELVIEWER_PERSPECTIVE_CAMERA_HPP
