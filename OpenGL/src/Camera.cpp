#include "Camera.h"

#include <GLFW/glfw3.h>

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_geometric.hpp"

Camera::Camera(GLFWwindow* window)
{
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    direction = glm::normalize(position - glm::vec3(0.0f, 0.0f, 0.0f));
    glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
    right = glm::normalize(glm::cross(worldUp, direction));
    up = glm::normalize(glm::cross(direction, right));

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
}

glm::mat4 Camera::LookAt(const glm::vec3& target)
{
    return glm::lookAt(position, target, up);
}

void Camera::OnUpdate(float deltaTimeX, GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position += cameraSpeed * direction * deltaTimeX;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position -= cameraSpeed * direction * deltaTimeX;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position -= glm::normalize(glm::cross(direction, up)) * cameraSpeed * deltaTimeX;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position += glm::normalize(glm::cross(direction, up)) * cameraSpeed * deltaTimeX;
    }
}

// static float lastMouseX = 400.0f, lastMouseY = 300.0f;
// static float pitch = 0, yaw = 0;

void Camera::mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    // float xOffset = xPos - lastMouseX;
    // float yOffset = lastMouseY - yPos; // reversed since y-coordinates range from bottom to top
    // lastMouseX = xPos;
    // lastMouseY = yPos;
    //
    // constexpr float sensitivity = 0.1f;
    // xOffset *= sensitivity;
    // yOffset *= sensitivity;
    //
    // yaw += xOffset;
    // pitch += yOffset;
    //
    // if (pitch > 89.0f)
    //     pitch = 89.0f;
    // if (pitch < -89.0f)
    //     pitch = -89.0f;
    //
    // glm::vec3 direction;
    // direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    // direction.y = sin(glm::radians(pitch));
    // direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    // direction = glm::normalize(direction);
}
