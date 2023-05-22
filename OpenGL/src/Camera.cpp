#include "Camera.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_geometric.hpp"

Camera::Camera()
{
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    direction = glm::normalize(position - glm::vec3(0.0f, 0.0f, 0.0f));
    glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
    right = glm::normalize(glm::cross(worldUp, direction));
    up = glm::normalize(glm::cross(direction, right));
}

glm::mat4 Camera::LookAt(const glm::vec3& target)
{
    return glm::lookAt(position, target, up);
}
