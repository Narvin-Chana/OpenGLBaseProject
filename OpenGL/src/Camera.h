#pragma once
#include "glm/fwd.hpp"
#include "glm/vec3.hpp"

class Camera
{
public:
    Camera();

    glm::mat4 LookAt(const glm::vec3& target);
    float cameraSpeed = 0.05f;
    glm::vec3 position, direction, right, up;
};
