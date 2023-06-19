#include "Camera.h"

#include <GLFW/glfw3.h>

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"

// Static variables declared for the mouse callback function
static float lastMouseX = 400.0f, lastMouseY = 300.0f;
static float pitch = 0, yaw = 0;
static bool firstMouse = true, mouseLook = false;
static Camera* cameraInstance = nullptr;

Camera::Camera(GLFWwindow* window)
{
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    direction = glm::normalize(position - glm::vec3(0.0f, 0.0f, 0.0f));
    glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
    right = glm::normalize(glm::cross(worldUp, direction));
    up = glm::normalize(glm::cross(direction, right));

    cameraInstance = this;
    glfwSetCursorPosCallback(window, mouse_callback);
    
}

glm::mat4 Camera::LookAt(const glm::vec3& target)
{
    return glm::lookAt(position, target, up);
}

void Camera::OnUpdate(float deltaTimeX, GLFWwindow* window)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[0] = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    io.MouseDown[1] = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
    io.MouseDown[2] = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;

    // Movement & camera controls
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
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        position += up * cameraSpeed * deltaTimeX;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        position -= up * cameraSpeed * deltaTimeX;
    }
    
    // Increase speed if the user holds down the left shift key
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        cameraSpeed = 7.0f;
    }
    else
    {
        cameraSpeed = 3.5f;
    }
    
    // Toggle mouseLook if the user presses the middle mouse button
    // This is useful for when the user wants to interact with the UI
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS && !isMiddleMouseButtonPressed)
    {
        isMiddleMouseButtonPressed = true;
        if (mouseLook == false)
        {
            mouseLook = true;
            firstMouse = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else
        {
            mouseLook = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
    else if (isMiddleMouseButtonPressed)
    {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE)
        {
            isMiddleMouseButtonPressed = false;
        }
    }
}

void Camera::mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    // Pass mouse info to ImGui
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(static_cast<float>(xPos), static_cast<float>(yPos));

    // Return if not mouseLook
    if (!mouseLook)
        return;

    // Explain the following line
    ImGui_ImplGlfw_MouseButtonCallback(window, GLFW_MOUSE_BUTTON_MIDDLE, GLFW_PRESS, 0);

    if (firstMouse)
    {
        lastMouseX = xPos;
        lastMouseY = yPos;
        firstMouse = false;
    }

    float xOffset = static_cast<float>(xPos) - lastMouseX;
    float yOffset = lastMouseY - static_cast<float>(yPos); // reversed since y-coordinates range from bottom to top
    lastMouseX = static_cast<float>(xPos);
    lastMouseY = static_cast<float>(yPos);

    constexpr float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraInstance->direction = glm::normalize(direction);
}
