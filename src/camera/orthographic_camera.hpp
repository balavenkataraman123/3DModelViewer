//
// Created by Gianni on 1/07/2024.
//

#ifndef INC_3DMODELVIEWER_ORTHOGRAPHIC_CAMERA_HPP
#define INC_3DMODELVIEWER_ORTHOGRAPHIC_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class OrthographicCamera
{
public:
    OrthographicCamera();
    OrthographicCamera(float left, float right, float bottom, float top, float near = 0.1f, float far = 100.f);

    const glm::mat4& projection() const;

private:
    glm::mat4 m_projection;
};


#endif //INC_3DMODELVIEWER_ORTHOGRAPHIC_CAMERA_HPP
