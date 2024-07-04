//
// Created by Gianni on 4/07/2024.
//

#ifndef INC_3DMODELVIEWER_CAMERA_HPP
#define INC_3DMODELVIEWER_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera
{
public:
    Camera();
    Camera(float width, float height, float fov, float near = 0.1f, float far = 100.f);
    Camera(float left, float right, float bottom, float top, float near = 0.1f, float far = 100.f);

    void set_position(const glm::vec3& position);
    void set_position(float x, float y, float z);
    void resize(float width, float height);

    const glm::mat4& projection() const;
    const glm::mat4& view() const;
    const glm::mat4& proj_view() const;
    const glm::vec3& position() const;

private:
    void recalculate_view();

private:
    glm::mat4 m_projection;
    glm::mat4 m_view;
    glm::mat4 m_proj_view;
    glm::vec3 m_position;
};


#endif //INC_3DMODELVIEWER_CAMERA_HPP
