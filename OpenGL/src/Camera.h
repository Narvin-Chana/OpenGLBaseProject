#pragma once
#include "glm/fwd.hpp"
#include "glm/vec3.hpp"

struct GLFWwindow;

/**
 * \brief This class should be instantiated only once.
 * Can contain only one reference to a camera.
 */
class Camera
{
public:
    glm::vec3 position, direction, right, up;

    Camera(GLFWwindow* window);
    ~Camera();

    glm::mat4 LookAt(const glm::vec3& target);
    static void mouse_callback(GLFWwindow* window, double xPos, double yPos);
    void OnUpdate(float deltaTimeX, GLFWwindow* window);
private:
    float cameraSpeed = 3.5f;
    bool isMiddleMouseButtonPressed = false;
    GLFWwindow* previouslyUsedWindow = nullptr;
};
