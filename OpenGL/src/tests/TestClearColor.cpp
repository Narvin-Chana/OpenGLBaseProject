#include "TestClearColor.h"

#include "Camera.h"
#include "Renderer.h"
#include "imgui/imgui.h"

namespace test
{
    TestClearColor::TestClearColor(GLFWwindow* w) : Test(w), clearColor{0.2f, 0.3f, 0.8f, 1.0f}
    {
    }

    TestClearColor::~TestClearColor() = default;

    void TestClearColor::OnUpdate(float deltaTime)
    {
        Test::OnUpdate(deltaTime);
    }

    void TestClearColor::OnRender()
    {
        Test::OnRender();

        GLCall(glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]))
        GLCall(glClear(GL_COLOR_BUFFER_BIT))
    }

    void TestClearColor::OnImGuiRender()
    {
        Test::OnImGuiRender();
        ImGui::ColorEdit4("Clear Color", clearColor);
    }
}
